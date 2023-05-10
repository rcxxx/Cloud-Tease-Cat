/**
 ******************************************************************************
 * @file           RPCProtocol.c
 * @description:   
 * @author:        Hare
 * @date:          2021-10-11
 * @version:       v0.1
 * @history: 
 *    [version]   [date]       [author]       [description]
 *    v0.1   	    2021-10-11   Hare           create
 *    v0.2   	    2022-01-28   Hare           add header CRC8
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "RPCProtocol.h"
#include <string.h>
#include <errno.h>
#include "RPCProtocol_cfg.h"

/* Defines -------------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
uint8_t RPCProtocol_rxIndex = 0;
uint8_t RPCProtocol_dataUpdate = 0;
uint8_t RPCProtocol_dataLength = 0;

/* Private macro -------------------------------------------------------------*/

/* Import function prototypes ------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
inline static uint8_t* RPCProtocol_getSrcDataBuffer(RPCProtocol_Header_t *header);

/* Exported functions --------------------------------------------------------*/
uint8_t RPCProtocol_dispatchInfo(uint8_t *p_data, uint16_t dataLength, __RPCProtocol_dispatchCallBack *cb)
{
  RPCProtocol_Header_t *pHeader = NULL;
  uint32_t fullDataSize = 0;
  uint32_t remainDataSize = 0;
  uint8_t *dataPtr = NULL;

  if(cb == NULL)
    return 0;

  if (dataLength < RPCPROTOCOL_PACKAGE_BASEDATALENGTH)
    return 0;

  /* 遍历数据包 */
  for (uint32_t n = 0; n < dataLength;)
  {
    /* 寻找帧头 */
    pHeader = (RPCProtocol_Header_t*)&p_data[n];
    remainDataSize = dataLength - n;
    if (pHeader->sof == RPCPROTOCOL_PACKAGE_SOF)
    {
      // if(RPCProtocol_VerifyCRC8(&p_data[n], RPCPROTOCOL_HEADER_BASEDATALENGTH))
      {
        /* 获取数据总长度 */
        fullDataSize = RPCPROTOCOL_GET_FULLDATALENGTH(pHeader->dataSize);

        if(fullDataSize <= remainDataSize)
        {
          // if(pHeader->devId == RPCProtocol_CFG_getDevID() || RPCPROTOCOL_BOCAST_DEVID == pHeader->devId)
          {
            /* 进行CRC校验 */
            // if (RPCProtocol_VerifyCRC16(&p_data[n], fullDataSize))
            {
              dataPtr = RPCProtocol_getSrcDataBuffer(pHeader);
              cb(pHeader->devId, pHeader->cmdId, dataPtr, pHeader->dataSize);
              break;

              /* 校验成功跳过这包继续寻找帧头 */
              n += fullDataSize;
            }
            // else
            // {
            //   /* 校验失败从下个包开始寻找帧头 */
            //   /* verify error, restart from next frame */
            //   n += fullDataSize;
            // }
          }
          // else
          // {
          //   /* dev id not match, break */
          //   n += fullDataSize;
          // }
        }
        else
        {
          /* size error, break */
          break;
          // n += fullDataSize;
        }
      }
      // else
      // {
      //   n++;
      // }
    }
    else
    {
      break;
      // n++;
    }
  }

  return 0;
}

uint16_t RPCProtocol_packInfo(uint8_t devId, uint8_t cmdId, \
                              const uint8_t *srcData, uint16_t srcSize, \
                              uint8_t *dstData, uint16_t dstSize)
{
  RPCProtocol_Header_t *pHeader = NULL;
  uint8_t *dataPtr = NULL;
  uint16_t fullDataSize = 0;

  if (NULL == srcData || NULL == dstData || 0 == srcSize || 0 == dstSize ||
      srcSize > (dstSize - RPCPROTOCOL_PACKAGE_BASEDATALENGTH))
  {
    return 0;
  }

  pHeader = (RPCProtocol_Header_t*)dstData;
  dataPtr = RPCProtocol_getSrcDataBuffer(pHeader);
  fullDataSize = RPCPROTOCOL_GET_FULLDATALENGTH(srcSize);

  pHeader->sof = RPCPROTOCOL_PACKAGE_SOF;
  pHeader->devId = devId;
  pHeader->cmdId = cmdId;
  pHeader->dataSize = srcSize;

  RPCProtocol_AppendCRC8(dstData, RPCPROTOCOL_HEADER_BASEDATALENGTH);

  memcpy(dataPtr, srcData, srcSize);

  RPCProtocol_AppendCRC16(dstData, fullDataSize);
  
  return fullDataSize;
}

int RPCProtocol_init(void)
{
  // RPCProtocol_CFG_init();
  // RPCProtocol_LL_Init();

  return 0;
}


/* Private functions ---------------------------------------------------------*/


static uint8_t* RPCProtocol_getSrcDataBuffer(RPCProtocol_Header_t *header)
{
  return (((uint8_t*)header) + RPCPROTOCOL_HEADER_BASEDATALENGTH);
}

