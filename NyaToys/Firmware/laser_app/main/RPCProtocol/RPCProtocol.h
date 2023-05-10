/**
 ******************************************************************************
 * @file           RPCProtocol.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RPCPROTOCOL_H__
#define __RPCPROTOCOL_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include "RPCProtocol_cfg.h"

/* Defines -------------------------------------------------------------------*/
/* PackageSOF(2-Byte)+Devid(1-Byte)+CmdID(1-Byte)+DataLength(1-Byte)+CRC8(1-Byte)+CRC16(2-Byte) */
#define RPCPROTOCOL_HEADER_BASEDATALENGTH    (sizeof(RPCProtocol_Header_t))
#define RPCPROTOCOL_PACKAGE_BASEDATALENGTH   (RPCPROTOCOL_HEADER_BASEDATALENGTH + 2)
#define RPCPROTOCOL_GET_FULLDATALENGTH(x)    (x + RPCPROTOCOL_PACKAGE_BASEDATALENGTH)

#define RPCPROTOCOL_FULLDATALENGTH_MAX       (256)
//#pragma anon_unions

/* Exported types ------------------------------------------------------------*/
typedef struct 
{
  uint16_t sof; /* Fixed 0xA5A5 */
  uint8_t devId;
  uint8_t cmdId;
  uint8_t dataSize;
  uint8_t crc8;
} RPCProtocol_Header_t;

typedef uint8_t __RPCProtocol_dispatchCallBack(uint8_t devId, uint8_t cmdId, uint8_t *pData, uint16_t length);

/* Exported constants --------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

int RPCProtocol_init(void);

uint8_t RPCProtocol_dispatchInfo(uint8_t *p_data, uint16_t dataLength, \
                                __RPCProtocol_dispatchCallBack *cb);
uint16_t RPCProtocol_packInfo(uint8_t devId, uint8_t cmdId, \
                              const uint8_t *srcData, uint16_t srcSize, \
                              uint8_t *dstData, uint16_t dstSize);



#ifdef __cplusplus
}
#endif

#endif /* __RPCPROTOCOL_H__ */
