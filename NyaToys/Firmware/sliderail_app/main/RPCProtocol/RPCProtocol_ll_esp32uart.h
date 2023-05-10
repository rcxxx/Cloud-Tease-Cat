/**
 ******************************************************************************
 * @file           RPCProtocol_ll_uart.h
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
#ifndef __RPCPROTOCOL_LL_ESP32UART_H__
#define __RPCPROTOCOL_LL_ESP32UART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Defines -------------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
int RPCProtocol_ESP32UART_init(void);
int RPCProtocol_ESP32UART_triggerSendPackage(uint8_t devId, uint8_t cmdId, uint8_t *pData, uint16_t size);

#ifdef __cplusplus
}
#endif

#endif /* __RPCPROTOCOL_LL_ESP32UART_H__ */
