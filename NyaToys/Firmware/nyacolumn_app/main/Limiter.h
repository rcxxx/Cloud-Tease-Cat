/**
 ******************************************************************************
 * @file           Limiter.h
 * @description:   
 * @author:        Hare
 * @date:          2023-01-23
 * @version:       v0.1
 * @history: 
 *    [version]   [date]       [author]       [description]
 *    v0.1   	    2023-01-23   Hare           create
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LIMITER_H__
#define __LIMITER_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Defines -------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  int8_t pin_num;
  uint8_t active_level;
} LimiterPin_t;

typedef struct 
{
  LimiterPin_t pin;
} Limiter_t;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
int Limiter_init(const Limiter_t *pCtx);
int Limiter_getStatus(const Limiter_t *pCtx);

#ifdef __cplusplus
}
#endif

#endif /* __LIMITER_H__ */
