/**
 ******************************************************************************
 * @file           RPCProtocol_ll_esp32uart.c
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
#include "RPCProtocol_ll_esp32uart.h"
#include "RPCProtocol_ll_esp32now.h"
#include "RPCProtocol.h"
#include "RPCProtocol_cfg.h"
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
#include "driver/uart.h"
#include "driver/gpio.h"


/* Defines -------------------------------------------------------------------*/
#define TAG "RPC_LL_ESPUART"

#define USING_UART      (UART_NUM_1)
#define UART_TXD_PIN    (GPIO_NUM_1)
#define UART_RXD_PIN    (GPIO_NUM_3)
// #define UART_TXD_PIN    (GPIO_NUM_4)
// #define UART_RXD_PIN    (GPIO_NUM_5)


#define RX_BUF_DEPTH    (2)
#define RX_BUF_SIZE     (512)

#define TX_BUF_DEPTH    (2)
#define TX_BUF_SIZE     (512)

#define ESPUART_RX_QUEUE_SIZE 6

/* Private types -------------------------------------------------------------*/
typedef struct
{
  uint8_t *data;
  int data_len;
} rpc_uart_rx_info_t;

/* Private constants ---------------------------------------------------------*/
static const uart_config_t uart_config = 
{
  .baud_rate = 115200,
  .data_bits = UART_DATA_8_BITS,
  .parity = UART_PARITY_DISABLE,
  .stop_bits = UART_STOP_BITS_1,
  .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
  .source_clk = UART_SCLK_APB,
};

/* Private variables ---------------------------------------------------------*/
static QueueHandle_t rpc_uart_evt_queue;
static QueueHandle_t s_espuart_rx_queue;

/* Private macro -------------------------------------------------------------*/

/* Import function prototypes ------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static esp_err_t rpc_uart_init(void);
static void rpc_uart_deinit(void);
static void uart_event_task(void *pvParameters);
static void rpc_uart_rx_task(void *arg);

/* Exported functions --------------------------------------------------------*/
int RPCProtocol_ESP32UART_init(void)
{
  rpc_uart_init();
  return 0;
}

int RPCProtocol_ESP32UART_deinit(void)
{
  rpc_uart_deinit();
  return 0;
}

int RPCProtocol_ESP32UART_triggerSendPackage(uint8_t devId, uint8_t cmdId, uint8_t *pData, uint16_t size)
{
  int ret = 0;
  uint8_t *pBuff = NULL;
  uint16_t fullDataSize = 0;
  
  fullDataSize = RPCPROTOCOL_GET_FULLDATALENGTH(size);
  if(fullDataSize > RPCPROTOCOL_FULLDATALENGTH_MAX)
  {
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

  uart_write_bytes(USING_UART, pBuff, ret);
  free(pBuff);

  return ESP_OK;
}

/* Private functions ---------------------------------------------------------*/
static esp_err_t rpc_uart_init(void)
{
  uart_driver_install(USING_UART, (RX_BUF_SIZE * RX_BUF_DEPTH), 
                                  (TX_BUF_SIZE * TX_BUF_DEPTH), 
                                  6, &rpc_uart_evt_queue, 0);
  uart_param_config(USING_UART, &uart_config);
  uart_set_pin(USING_UART, UART_TXD_PIN, UART_RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

  s_espuart_rx_queue = xQueueCreate(ESPUART_RX_QUEUE_SIZE, sizeof(rpc_uart_rx_info_t));

  //Create a task to handler UART event from ISR
  xTaskCreate(uart_event_task, "uart_event_task", 2048, NULL, 4, NULL);
  xTaskCreate(rpc_uart_rx_task, "rpc_uart_rx_task", 2048, NULL, 4, NULL);

  return ESP_OK;
}

static void rpc_uart_deinit(void)
{
  // vSemaphoreDelete(s_espnow_cb_queue);
  // esp_now_deinit();
}

static void uart_event_task(void *pvParameters)
{
  uart_event_t event;

  while (1)
  {
    // Waiting for UART event.
    if (xQueueReceive(rpc_uart_evt_queue, (void *)&event, portMAX_DELAY))
    {
      ESP_LOGD(TAG, "uart[%d] event:", USING_UART);
      switch (event.type)
      {
        // Event of UART receving data
        /*We'd better handler data event fast, there would be much more data events than
        other types of events. If we take too much time on data event, the queue might
        be full.*/
        case UART_DATA:
        {
          rpc_uart_rx_info_t rx_info;
          uint8_t *pBuff = NULL;

          ESP_LOGD(TAG, "[UART DATA]: %d", event.size);
          pBuff = malloc(event.size);
          if (pBuff == NULL)
          {
            /* no mem, drop */
            uart_flush_input(USING_UART);
            xQueueReset(rpc_uart_evt_queue);
          }
          else
          {
            rx_info.data_len = uart_read_bytes(USING_UART, pBuff, event.size, portMAX_DELAY);
            rx_info.data = pBuff;
            if (xQueueSend(s_espuart_rx_queue, &rx_info, pdMS_TO_TICKS(10)) != pdTRUE)
            {
              ESP_LOGW(TAG, "Send receive queue fail");
              free(rx_info.data);
            }
          }
        }
        break;
        // Event of HW FIFO overflow detected
        case UART_FIFO_OVF:
          ESP_LOGI(TAG, "hw fifo overflow");
          // If fifo overflow happened, you should consider adding flow control for your application.
          // The ISR has already reset the rx FIFO,
          // As an example, we directly flush the rx buffer here in order to read more data.
          uart_flush_input(USING_UART);
          xQueueReset(rpc_uart_evt_queue);
          break;
        // Event of UART ring buffer full
        case UART_BUFFER_FULL:
          ESP_LOGI(TAG, "ring buffer full");
          // If buffer full happened, you should consider encreasing your buffer size
          // As an example, we directly flush the rx buffer here in order to read more data.
          uart_flush_input(USING_UART);
          xQueueReset(rpc_uart_evt_queue);
          break;
        // Event of UART RX break detected
        case UART_BREAK:
          ESP_LOGI(TAG, "uart rx break");
          break;
        // Event of UART parity check error
        case UART_PARITY_ERR:
          ESP_LOGI(TAG, "uart parity error");
          break;
        // Event of UART frame error
        case UART_FRAME_ERR:
          ESP_LOGI(TAG, "uart frame error");
          break;
        default:
          break;
      }
    }
  }
  vTaskDelete(NULL);
}

static void rpc_uart_rx_task(void *arg)
{
  rpc_uart_rx_info_t rx_info;

  while (1)
  {
    if(xQueueReceive(s_espuart_rx_queue, &rx_info, portMAX_DELAY) == pdTRUE)
    {
      ESP_LOGD(TAG, "revc: %d", rx_info.data_len);
      /* Handle data */
      RPCProtocol_ESP32Now_triggerBroadcastRaw(rx_info.data, rx_info.data_len);
      // RPCProtocol_dispatchInfo(rx_info.data, rx_info.data_len, RPCProtocol_ESPUART_dispatchHandler);
      free(rx_info.data);
    }
  }
  vTaskDelete(NULL);
}
