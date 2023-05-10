/**
 ******************************************************************************
 * @file           RPCProtocol_cfg.h
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
#ifndef __RPCPROTOCOL_CFG_H__
#define __RPCPROTOCOL_CFG_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#if defined __DEV_STM32__
#include "RPCProtocol_ll_stm32hal.h"
#elif defined __DEV_PCQT__

#elif defined CONFIG_IDF_TARGET_ESP32 || defined CONFIG_IDF_TARGET_ESP32C3

#endif

/* Defines -------------------------------------------------------------------*/
#define RPCPROTOCOL_PACKAGE_SOF              (0xA5A5u)

#define RPCPROTOCOL_PCTOOLS_DEVID            (0x00u)
#define RPCPROTOCOL_BOCAST_DEVID             (0xFFu)
#define RPCPROTOCOL_SENDTOALL_DEVID          (0xFEu)

#define RPCPROTOCOL_DEVIDMAX                 (16)

#define ESP_NOW_ETH_MACLEN                   (6)

/* Private types -------------------------------------------------------------*/
typedef enum
{
  RPCPROTOCOL_CMDID_TRIGGER_STOP = 0x00,
  RPCPROTOCOL_CMDID_TRIGGER_RANDOM_MOVE = 0x01,
  RPCPROTOCOL_CMDID_TRIGGER_RANDOM_MOVE2 = 0x02,
  
} RPCProtocol_CmdId_t;

typedef void __RPCProtocol_Callback_t(uint8_t *p_data, uint16_t dataLength);
typedef struct
{
  uint16_t eventID;
  __RPCProtocol_Callback_t *cb;
} RPCProtocol_CallbackList_t;

typedef struct
{
  uint8_t dummy;
} RPCProtocol_DummyData_t;

typedef struct
{
  uint8_t result;
} RPCProtocol_CommOptAck_t;

/* Private constants ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
// uint8_t RPCProtocol_CFG_init(void);
uint8_t RPCProtocol_CFG_getDevID(void);
#if defined CONFIG_IDF_TARGET_ESP32 || defined CONFIG_IDF_TARGET_ESP32C3
uint8_t RPCProtocol_ESPNOW_dispatchHandler(uint8_t devId, uint8_t cmdId, uint8_t *pData, uint16_t length);
uint8_t RPCProtocol_ESPUART_dispatchHandler(uint8_t devId, uint8_t cmdId, uint8_t *pData, uint16_t length);
#endif

#if defined __DEV_PCQT__
uint8_t RPCProtocol_QTSerial_dispatchHandler(uint8_t devId, uint8_t cmdId, uint8_t *pData, uint16_t length);
void RPCProtocol_QTSerial_commOptAck_cb(uint8_t *pData, uint16_t size);
#endif

uint32_t RPCProtocol_VerifyCRC8(uint8_t *pchMessage, uint32_t dwLength);
void RPCProtocol_AppendCRC8(uint8_t *pchMessage, uint32_t dwLength);
uint32_t RPCProtocol_VerifyCRC16(uint8_t *pchMessage, uint32_t dwLength);
void RPCProtocol_AppendCRC16(uint8_t * pchMessage, uint32_t dwLength);

/* Exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __RPCPROTOCOL_CFG_H__ */
