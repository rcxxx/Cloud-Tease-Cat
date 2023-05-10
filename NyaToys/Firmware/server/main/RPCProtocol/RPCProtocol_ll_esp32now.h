/**
 ******************************************************************************
 * @file           RPCProtocol_ll_esp32now.h
 * @description:   
 * @author:        Hare
 * @date:          2021-10-16
 * @version:       v0.1
 * @history: 
 *    [version]   [date]       [author]       [description]
 *    v0.1   	    2021-10-16   Hare           create
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RPCPROTOCOL_LL_ESP32NOW_H__
#define __RPCPROTOCOL_LL_ESP32NOW_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
// #include "esp_now.h"

/* Defines -------------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/
typedef struct
{
  uint8_t *mac_addr;
  uint8_t *data;
  int data_len;
} espnow_tx_info_t;

typedef enum
{
  RPCPROTOCOL_ESP32NOW_BOCASTING = 0,
  RPCPROTOCOL_ESP32NOW_CONNECTED,
} RPCProtocol_ESP32Now_ConnSM_t;

/* Private constants ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
int RPCProtocol_ESP32Now_init(void);
int RPCProtocol_ESP32Now_findMACByDevID(uint8_t devId, uint8_t **mac);
int RPCProtocol_ESP32Now_peerDev(uint8_t devId, const uint8_t *mac);
uint32_t RPCProtocol_ESP32Now_getConnectedFlags(void);
int RPCProtocol_ESP32Now_triggerSendPackage(uint8_t devId, uint8_t cmdId, uint8_t *pData, uint16_t size);
int RPCProtocol_ESP32Now_triggerBroadcastRaw(uint8_t *pData, uint16_t size);
uint8_t *RPCProtocol_ESP32Now_getSelfMAC(void);
void RPCProtocol_ESP32Now_setConnSM(RPCProtocol_ESP32Now_ConnSM_t newStaus);

#ifdef __cplusplus
}
#endif

#endif /* __RPCPROTOCOL_LL_ESP32NOW_H__ */
