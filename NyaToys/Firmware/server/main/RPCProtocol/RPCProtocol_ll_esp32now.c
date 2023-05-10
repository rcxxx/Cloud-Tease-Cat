/**
 ******************************************************************************
 * @file           RPCProtocol_ll_esp32now.c
 * @description:
 * @author:        Hare
 * @date:          2021-10-16
 * @version:       v0.1
 * @history:
 *    [version]   [date]       [author]       [description]
 *    v0.1   	    2021-10-16   Hare           create
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "RPCProtocol_ll_esp32now.h"
#include "RPCProtocol.h"
#include "SysLog.h"
#include <string.h>
#include <errno.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_now.h"
#include "esp_mac.h"


/* Defines -------------------------------------------------------------------*/
#define TAG "RPC_LL_ESPNOW"

#define CONFIG_ESPNOW_PMK "pmk16a5713600a2d"
#define CONFIG_ESPNOW_LMK "lmk16a5713600a2d"
#define CONFIG_ESPNOW_CHANNEL 12
#define CONFIG_ESPNOW_WIFI_MODE_STATION 1

/* ESPNOW can work in both station and softap mode. It is configured in menuconfig. */
#if CONFIG_ESPNOW_WIFI_MODE_STATION
#define ESPNOW_WIFI_MODE WIFI_MODE_STA
#define ESPNOW_WIFI_IF ESP_IF_WIFI_STA
#else
#define ESPNOW_WIFI_MODE WIFI_MODE_AP
#define ESPNOW_WIFI_IF ESP_IF_WIFI_AP
#endif

#define ESPNOW_CB_QUEUE_SIZE 6
#define ESPNOW_TX_QUEUE_SIZE 6
#define ESPNOW_MAXDELAY 512

#define RPCPROTOCOL_RXBUFFER_DEPTH  2
#define RPCPROTOCOL_RXBUFFER_SIZE   255

#define RPCPROTOCOL_TXBUFFER_DEPTH  2
#define RPCPROTOCOL_TXBUFFER_SIZE   255

#define RPCPROTOCOL_MACLIST_NUM     ESP_NOW_MAX_TOTAL_PEER_NUM

/* Private types -------------------------------------------------------------*/
typedef enum
{
  ESPNOW_EVENT_SEND_CB,
  ESPNOW_EVENT_RECV_CB,
} espnow_event_id_t;

typedef struct
{
  uint8_t mac_addr[ESP_NOW_ETH_ALEN];
  esp_now_send_status_t status;
} espnow_event_send_cb_t;

typedef struct
{
  uint8_t mac_addr[ESP_NOW_ETH_ALEN];
  uint8_t *data;
  int data_len;
} espnow_event_recv_cb_t;

typedef union
{
  espnow_event_send_cb_t send_cb;
  espnow_event_recv_cb_t recv_cb;
} espnow_event_info_t;

/* When ESPNOW sending or receiving callback function is called, post event to ESPNOW task. */
typedef struct
{
  espnow_event_id_t id;
  espnow_event_info_t info;
} espnow_event_t;


uint8_t *RPCProtocol_MACList[RPCPROTOCOL_MACLIST_NUM];
static uint32_t connectedFlags = 0;

/* Private constants ---------------------------------------------------------*/
static const uint8_t espnow_broadcast_mac[ESP_NOW_ETH_ALEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static uint8_t espnow_self_mac[ESP_NOW_ETH_ALEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

/* Private variables ---------------------------------------------------------*/
static QueueHandle_t s_espnow_cb_queue;
static QueueHandle_t s_espnow_tx_queue;
static RPCProtocol_ESP32Now_ConnSM_t connSM = RPCPROTOCOL_ESP32NOW_BOCASTING;

/* Private macro -------------------------------------------------------------*/
#define IS_BROADCAST_ADDR(addr) (memcmp(addr, espnow_broadcast_mac, ESP_NOW_ETH_ALEN) == 0)

/* Import function prototypes ------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void espnow_wifi_init(void);
static esp_err_t espnow_init(void);
static void espnow_deinit(void);
static int espnow_peer_device(const uint8_t *peer_addr);
static void espnow_send_cb(const uint8_t *mac_addr, esp_now_send_status_t status);
static void espnow_recv_cb(const esp_now_recv_info_t *esp_now_info, const uint8_t *data, int len);
static void espnow_cb_task(void *pvParameter);
static void espnow_tx_task(void *pvParameter);

/* Exported functions --------------------------------------------------------*/
int RPCProtocol_ESP32Now_init(void)
{
  // RPCProtocol_init();
  
  for(int i = 0; i < RPCPROTOCOL_MACLIST_NUM; i++)
  {
    RPCProtocol_MACList[i] = NULL;
  }

  espnow_wifi_init();
  espnow_init();
  return 0;
}

int RPCProtocol_ESP32Now_findMACByDevID(uint8_t devId, uint8_t **mac)
{
  int ret = 0;
  if(mac == NULL)
  {
    return EINVAL;
  }
  
  if(devId == RPCPROTOCOL_BOCAST_DEVID)
  {
    *mac = (uint8_t*)espnow_broadcast_mac;
  }
  else if(devId == RPCProtocol_CFG_getDevID())
  {
    *mac = espnow_self_mac;
  }
  else if(devId == RPCPROTOCOL_SENDTOALL_DEVID)
  {
    *mac = NULL;
  }
  else
  {
    if(devId < RPCPROTOCOL_MACLIST_NUM)
    {
      if(RPCProtocol_MACList[devId] == NULL)
      {
        ret = ENODEV;
      }
      else
      {
        *mac = RPCProtocol_MACList[devId];
      }
    }
    else
    {
      ret = EINVAL;
    }
  }
  return ret;
}

int RPCProtocol_ESP32Now_peerDev(uint8_t devId, const uint8_t *mac)
{
  int ret = 0;
  uint8_t *newMAC = NULL;

  if(mac == NULL || devId > RPCPROTOCOL_MACLIST_NUM)
  {
    return EINVAL;
  }

  newMAC = malloc(ESP_NOW_ETH_ALEN);
  if (newMAC == NULL)
  {
    ESP_LOGE(TAG, "Malloc peer information fail");
    return ESP_ERR_NO_MEM;
  }

  memcpy(newMAC, mac, ESP_NOW_ETH_ALEN);
  ret = espnow_peer_device(newMAC);
  if(ret != ESP_OK)
  {
    free(newMAC);
  }

  if(RPCProtocol_MACList[devId] != NULL)
  {
    free(RPCProtocol_MACList[devId]);
  }
  RPCProtocol_MACList[devId] = newMAC;
  connectedFlags |= 1 << devId;

  SYS_LOGI(TAG, "peer device, devid:%d, mac " MACSTR, devId, MAC2STR(newMAC));

  return ret;
}

uint32_t RPCProtocol_ESP32Now_getConnectedFlags(void)
{
  return connectedFlags;
}

int RPCProtocol_ESP32Now_triggerSendPackage(uint8_t devId, uint8_t cmdId, uint8_t *pData, uint16_t size)
{
  espnow_tx_info_t tx_info;
  int ret = 0;
  uint8_t *pBuff = NULL;
  uint16_t fullDataSize = 0;
  
  fullDataSize = RPCPROTOCOL_GET_FULLDATALENGTH(size);
  if(fullDataSize > RPCPROTOCOL_FULLDATALENGTH_MAX)
  {
    SYS_LOGE(TAG, "ERR: Data too long %d>%d", fullDataSize, RPCPROTOCOL_FULLDATALENGTH_MAX);
    return EINVAL;
  }

  ret = RPCProtocol_ESP32Now_findMACByDevID(devId, &tx_info.mac_addr);
  if(ret != 0)
  {
    SYS_LOGE(TAG, "ERR: MAC Can not found");
    return EINVAL;
  }

  pBuff = malloc(fullDataSize);
  if (pBuff == NULL)
  {
    SYS_LOGE(TAG, "ERR: Malloc TXbuff");
    return ENOMEM;
  }

  ret = RPCProtocol_packInfo(devId, cmdId, \
                              pData, size, \
                              pBuff, fullDataSize);
  if(ret == 0)
  {
    SYS_LOGE(TAG, "%s: packInfo err", __func__);
    return EINVAL;
  }

  tx_info.data = pBuff;
  tx_info.data_len = ret;

  /* Trigger TX Task */
  if (xQueueSend(s_espnow_tx_queue, &tx_info, ESPNOW_MAXDELAY) != pdTRUE)
  {
    ESP_LOGE(TAG, "Trigger TX queue fail");
    free(tx_info.data);
  }

  return ESP_OK;
}

int RPCProtocol_ESP32Now_triggerBroadcastRaw(uint8_t *pData, uint16_t size)
{
  espnow_tx_info_t tx_info;
  int ret = 0;
  uint8_t *pBuff = NULL;
  uint16_t fullDataSize = 0;
  
  fullDataSize = size;
  if(fullDataSize > RPCPROTOCOL_FULLDATALENGTH_MAX)
  {
    SYS_LOGE(TAG, "ERR: Data too long %d>%d", fullDataSize, RPCPROTOCOL_FULLDATALENGTH_MAX);
    return EINVAL;
  }

  tx_info.mac_addr = (uint8_t*)espnow_broadcast_mac;

  pBuff = malloc(fullDataSize);
  if (pBuff == NULL)
  {
    SYS_LOGE(TAG, "ERR: Malloc TXbuff");
    return ENOMEM;
  }

  memcpy(pBuff, pData, fullDataSize);

  tx_info.data = pBuff;
  tx_info.data_len = fullDataSize;

  /* Trigger TX Task */
  if (xQueueSend(s_espnow_tx_queue, &tx_info, ESPNOW_MAXDELAY) != pdTRUE)
  {
    ESP_LOGE(TAG, "Trigger TX queue fail");
    free(tx_info.data);
  }

  return ESP_OK;
}

uint8_t *RPCProtocol_ESP32Now_getSelfMAC(void)
{
  return espnow_self_mac;
}

void RPCProtocol_ESP32Now_setConnSM(RPCProtocol_ESP32Now_ConnSM_t newStaus)
{
  connSM = newStaus;
}

/* Private functions ---------------------------------------------------------*/


/* WiFi should start before using ESPNOW */
static void espnow_wifi_init(void)
{
  ESP_ERROR_CHECK(esp_netif_init());
  ESP_ERROR_CHECK(esp_event_loop_create_default());
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK(esp_wifi_init(&cfg));
  ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
  ESP_ERROR_CHECK(esp_wifi_set_mode(ESPNOW_WIFI_MODE));
  ESP_ERROR_CHECK(esp_wifi_start());

#if CONFIG_ESPNOW_ENABLE_LONG_RANGE
  ESP_ERROR_CHECK(esp_wifi_set_protocol(ESPNOW_WIFI_IF, WIFI_PROTOCOL_11B | WIFI_PROTOCOL_11G | WIFI_PROTOCOL_11N | WIFI_PROTOCOL_LR));
#endif
}

static esp_err_t espnow_init(void)
{
  int ret = ESP_OK;
  s_espnow_cb_queue = xQueueCreate(ESPNOW_CB_QUEUE_SIZE, sizeof(espnow_event_t));
  if (s_espnow_cb_queue == NULL)
  {
    ESP_LOGE(TAG, "Create mutex fail");
    return ESP_FAIL;
  }
  s_espnow_tx_queue = xQueueCreate(ESPNOW_TX_QUEUE_SIZE, sizeof(espnow_tx_info_t));
  if (s_espnow_tx_queue == NULL)
  {
    ESP_LOGE(TAG, "Create mutex fail");
    vSemaphoreDelete(s_espnow_cb_queue);
    return ESP_FAIL;
  }

  ESP_ERROR_CHECK(esp_wifi_set_channel(CONFIG_ESPNOW_CHANNEL, WIFI_SECOND_CHAN_NONE));

  /* Initialize ESPNOW and register sending and receiving callback function. */
  ESP_ERROR_CHECK(esp_now_init());
  ESP_ERROR_CHECK(esp_now_register_send_cb(espnow_send_cb));
  ESP_ERROR_CHECK(esp_now_register_recv_cb(espnow_recv_cb));

  /* get my MAC */
  ret = esp_base_mac_addr_get(espnow_self_mac);
  if(ret != ESP_OK)
  {
    ESP_LOGE(TAG, "get base MAC fail");
  }

  /* Set primary master key. */
  ESP_ERROR_CHECK(esp_now_set_pmk((uint8_t *)CONFIG_ESPNOW_PMK));

  /* Add broadcast peer information to peer list. */
  esp_now_peer_info_t *peer = malloc(sizeof(esp_now_peer_info_t));
  if (peer == NULL)
  {
    ESP_LOGE(TAG, "Malloc peer information fail");
    vSemaphoreDelete(s_espnow_cb_queue);
    vSemaphoreDelete(s_espnow_tx_queue);
    esp_now_deinit();
    return ESP_FAIL;
  }
  memset(peer, 0, sizeof(esp_now_peer_info_t));
  peer->channel = CONFIG_ESPNOW_CHANNEL;
  peer->ifidx = ESPNOW_WIFI_IF;
  peer->encrypt = false;
  memcpy(peer->peer_addr, espnow_broadcast_mac, ESP_NOW_ETH_ALEN);
  ESP_ERROR_CHECK(esp_now_add_peer(peer));
  free(peer);

  xTaskCreate(espnow_cb_task, "espnow_cb_task", 4096, NULL, 4, NULL);
  xTaskCreate(espnow_tx_task, "espnow_tx_task", 4096, NULL, 4, NULL);
  // xTaskCreate(espnow_connSM_task, "espnow_connSM_task", 2048, NULL, 4, NULL);

  return ESP_OK;
}

static void espnow_deinit(void)
{
  vSemaphoreDelete(s_espnow_cb_queue);
  esp_now_deinit();
}

static int espnow_peer_device(const uint8_t *peer_addr)
{
  int ret = ESP_OK;
  if (esp_now_is_peer_exist(peer_addr) == false)
  {
    esp_now_peer_info_t *peer = malloc(sizeof(esp_now_peer_info_t));
    if (peer == NULL)
    {
      ESP_LOGE(TAG, "Malloc peer information fail");
      return ESP_ERR_NO_MEM;
    }
    memset(peer, 0, sizeof(esp_now_peer_info_t));
    peer->channel = CONFIG_ESPNOW_CHANNEL;
    peer->ifidx = ESPNOW_WIFI_IF;
    // peer->encrypt = true;
    peer->encrypt = false;
    memcpy(peer->lmk, CONFIG_ESPNOW_LMK, ESP_NOW_KEY_LEN);
    memcpy(peer->peer_addr, peer_addr, ESP_NOW_ETH_ALEN);
    ret = esp_now_add_peer(peer);
    ESP_ERROR_CHECK(ret);
    free(peer);
  }
  return ret;
}

/* ESPNOW sending or receiving callback function is called in WiFi task.
 * Users should not do lengthy operations from this task. Instead, post
 * necessary data to a queue and handle it from a lower priority task. */
static void espnow_send_cb(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  espnow_event_t evt;
  espnow_event_send_cb_t *send_cb = &evt.info.send_cb;

  if (mac_addr == NULL)
  {
    ESP_LOGE(TAG, "Send cb arg error");
    return;
  }

  evt.id = ESPNOW_EVENT_SEND_CB;
  memcpy(send_cb->mac_addr, mac_addr, ESP_NOW_ETH_ALEN);
  send_cb->status = status;
  if (xQueueSend(s_espnow_cb_queue, &evt, ESPNOW_MAXDELAY) != pdTRUE)
  {
    ESP_LOGW(TAG, "Send send queue fail");
  }
}

static void espnow_recv_cb(const esp_now_recv_info_t *esp_now_info, const uint8_t *data, int len)
{
  espnow_event_t evt;
  espnow_event_recv_cb_t *recv_cb = &evt.info.recv_cb;
  uint8_t *mac_addr = NULL;
  if (esp_now_info == NULL || data == NULL || len <= 0)
  {
    ESP_LOGE(TAG, "Receive cb arg error");
    return;
  }

  mac_addr = esp_now_info->src_addr;
  evt.id = ESPNOW_EVENT_RECV_CB;
  memcpy(recv_cb->mac_addr, mac_addr, ESP_NOW_ETH_ALEN);
  recv_cb->data = malloc(len);
  if (recv_cb->data == NULL)
  {
    ESP_LOGE(TAG, "Malloc receive data fail");
    return;
  }
  memcpy(recv_cb->data, data, len);
  recv_cb->data_len = len;
  if (xQueueSend(s_espnow_cb_queue, &evt, ESPNOW_MAXDELAY) != pdTRUE)
  {
    ESP_LOGW(TAG, "Send receive queue fail");
    free(recv_cb->data);
  }
}

static void espnow_cb_task(void *pvParameter)
{
  espnow_event_t evt;
  bool is_broadcast = false;
  // int ret = ESP_OK;

  while (1)
  {
    if(xQueueReceive(s_espnow_cb_queue, &evt, portMAX_DELAY) == pdTRUE)
    {
      switch (evt.id)
      {
        case ESPNOW_EVENT_SEND_CB:
        {
          espnow_event_send_cb_t *send_cb = &evt.info.send_cb;
          is_broadcast = IS_BROADCAST_ADDR(send_cb->mac_addr);

          ESP_LOGD(TAG, "Send data to " MACSTR ", status1: %d", MAC2STR(send_cb->mac_addr), send_cb->status);
        }
        break;
        case ESPNOW_EVENT_RECV_CB:
        {
          espnow_event_recv_cb_t *recv_cb = &evt.info.recv_cb;
          is_broadcast = IS_BROADCAST_ADDR(recv_cb->mac_addr);

          // ESP_LOGI(TAG, "Receive data from: " MACSTR ", len: %d", MAC2STR(recv_cb->mac_addr), recv_cb->data_len);

          /* Handle data */
          // RPCProtocol_dispatchInfo(recv_cb->data, recv_cb->data_len, RPCProtocol_ESPNOW_dispatchHandler);
          free(recv_cb->data);
        }
        break;
        default:
        {
          ESP_LOGE(TAG, "Callback type error: %d", evt.id);
        }
        break;
      }
    }
  }
  vTaskDelete(NULL);
}

static void espnow_tx_task(void *pvParameter)
{
  espnow_tx_info_t tx_info;
  int ret = ESP_OK;

  while (1)
  {
    if(xQueueReceive(s_espnow_tx_queue, &tx_info, portMAX_DELAY) == pdTRUE)
    {
      ret = esp_now_send(tx_info.mac_addr, tx_info.data, tx_info.data_len);
      free(tx_info.data);

      if(ret != ESP_OK)
      {
        if(tx_info.mac_addr != NULL)
        {
          ESP_LOGE(TAG, "Send data to " MACSTR " failed: %d", MAC2STR(tx_info.mac_addr), ret);
        }
        else
        {
          if(ret != ESP_ERR_ESPNOW_NOT_FOUND)
          {
            ESP_LOGE(TAG, "Send data to all peer failed: %d", ret);
          }
        }
      }
      // vTaskDelay(1);
    }
  }
  vTaskDelete(NULL);
}

