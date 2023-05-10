/**
 ******************************************************************************
 * @file           rpc_cmd_cb.h
 * @description:   
 * @author:        Hare
 * @date:          2022-09-25
 * @version:       v0.1
 * @history: 
 *    [version]   [date]       [author]       [description]
 *    v0.1   	    2022-09-25   Hare           create
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RPC_CMD_CB_H__
#define __RPC_CMD_CB_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Defines -------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void RPCCMD_triggerRandomMove_cb(uint8_t *pData, uint16_t size);

#ifdef __cplusplus
}
#endif

#endif /* __RPC_CMD_CB_H__ */
