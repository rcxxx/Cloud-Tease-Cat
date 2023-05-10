/**
 ******************************************************************************
 * @file           RPCProtocol_cfg_qt.c
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
#include "RPCProtocol_cfg.h"
#include "RPCProtocol.h"
#include "crc.h"
#if defined __DEV_STM32__
#include "RPCTask.h"
#include "EventRecorder.h"
#elif defined __DEV_PCQT__

#elif defined CONFIG_IDF_TARGET_ESP32 || defined CONFIG_IDF_TARGET_ESP32C3
#include "rpc_cmd_cb.h"
// #include "settings.h"
#include "RPCProtocol_ll_esp32now.h"
#include "RPCProtocol_ll_esp32uart.h"
#include "SysLog.h"
#endif

/* Defines -------------------------------------------------------------------*/
#define TAG   "RPC_CFG"

/* Private types -------------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
const RPCProtocol_CallbackList_t RPCProtocol_ESPUART_CallbackList[] = 
{
};

const RPCProtocol_CallbackList_t RPCProtocol_ESPNOW_CallbackList[] = 
{
  {RPCPROTOCOL_CMDID_TRIGGER_RANDOM_MOVE,      RPCCMD_triggerRandomMove_cb},

};

/* Private variables ---------------------------------------------------------*/
uint8_t RPCProtocol_DevID = 0x00;

/* Private macro -------------------------------------------------------------*/

/* Import function prototypes ------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
uint8_t RPCProtocol_CFG_init(void)
{
  return 0;
}

uint8_t RPCProtocol_CFG_getDevID(void)
{
#if defined CONFIG_IDF_TARGET_ESP32 || defined CONFIG_IDF_TARGET_ESP32C3
  return RPCProtocol_DevID;
#else
  return 0;
#endif
}

uint8_t RPCProtocol_ESPNOW_dispatchHandler(uint8_t devId, uint8_t cmdId, uint8_t *pData, uint16_t length)
{
  SYS_LOGI(__FILE__, "%s: entry, devid:%d, cmdid%d", __func__, devId, cmdId);
  if ((devId == RPCProtocol_CFG_getDevID()) /* || (devId == RPCPROTOCOL_BOCAST_DEVID) || (devId == RPCPROTOCOL_SENDTOALL_DEVID) */)
  {
    int cb_size = sizeof(RPCProtocol_ESPNOW_CallbackList)/sizeof(RPCProtocol_CallbackList_t);
    // if(RPCProtocol_CFG_getDevID() == RPCPROTOCOL_PCTOOLS_DEVID && cmdId >= RPCPROTOCOL_CMDID_COMMOPTACK)
    // {
    //   RPCProtocol_ESP32UART_triggerSendPackage(devId, cmdId, pData, length);
    // }
    // else
    {
      for (int i = 0; i < cb_size; i++)
      {
        if (cmdId == RPCProtocol_ESPNOW_CallbackList[i].eventID)
        {
          if (RPCProtocol_ESPNOW_CallbackList[i].cb != NULL)
          {
            RPCProtocol_ESPNOW_CallbackList[i].cb(pData, length);
          }
          break;
        }
      }
    }
    
  }
  else
  {
  }
  return 0;
}


uint8_t RPCProtocol_ESPUART_dispatchHandler(uint8_t devId, uint8_t cmdId, uint8_t *pData, uint16_t length)
{
  if (devId == RPCPROTOCOL_PCTOOLS_DEVID)
  {
    int cb_size = sizeof(RPCProtocol_ESPUART_CallbackList)/sizeof(RPCProtocol_CallbackList_t);
    for (int i = 0; i < cb_size; i++)
    {
      if (cmdId == RPCProtocol_ESPUART_CallbackList[i].eventID)
      {
        if (RPCProtocol_ESPUART_CallbackList[i].cb != NULL)
        {
          RPCProtocol_ESPUART_CallbackList[i].cb(pData, length);
        }
        break;
      }
    }
  }
  else
  {
    RPCProtocol_ESP32Now_triggerSendPackage(devId, cmdId, pData, length);
  }
  return 0;
}

/* Private functions ---------------------------------------------------------*/
uint32_t RPCProtocol_VerifyCRC8(uint8_t *pchMessage, uint32_t dwLength)
{
  return CRC8_VerifyCheckSum(pchMessage, dwLength);
}

void RPCProtocol_AppendCRC8(uint8_t *pchMessage, uint32_t dwLength)
{
  CRC8_AppendCheckSum(pchMessage, dwLength);
}

uint32_t RPCProtocol_VerifyCRC16(uint8_t *pchMessage, uint32_t dwLength)
{
  return CRC16_VerifyCheckSum(pchMessage, dwLength);
}

void RPCProtocol_AppendCRC16(uint8_t * pchMessage, uint32_t dwLength)
{
  CRC16_AppendCheckSum(pchMessage, dwLength);
}
