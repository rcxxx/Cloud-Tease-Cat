/**
 ******************************************************************************
 * @file           crc.h
 * @description:   
 * @author:        Hare
 * @date:          2021-10-10
 * @version:       v0.1
 * @history: 
 *    [version]   [date]       [author]       [description]
 *    v0.1   	    2021-10-10   Hare           create
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CRC_H__
#define __CRC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>

/* Defines -------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
extern uint8_t CRC8_GetCheckSum(uint8_t *pchMessage, uint32_t dwLength, uint8_t ucCRC8);
extern uint32_t CRC8_VerifyCheckSum(uint8_t *pchMessage, uint32_t dwLength);
extern void CRC8_AppendCheckSum(uint8_t *pchMessage, uint32_t dwLength);

extern uint16_t CRC16_GetCheckSum(uint8_t *pchMessage,uint32_t dwLength, uint16_t wCRC);
extern uint32_t CRC16_VerifyCheckSum(uint8_t *pchMessage, uint32_t dwLength);
extern void CRC16_AppendCheckSum(uint8_t * pchMessage, uint32_t dwLength);


#ifdef __cplusplus
}
#endif

#endif /* __CRC_H__ */
