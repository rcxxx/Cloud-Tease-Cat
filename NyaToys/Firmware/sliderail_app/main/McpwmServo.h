/**
 ******************************************************************************
 * @file           McpwmServo.h
 * @description:   
 * @author:        Hare
 * @date:          2023-01-21
 * @version:       v0.1
 * @history: 
 *    [version]   [date]       [author]       [description]
 *    v0.1   	    2023-01-21   Hare           create
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MCPWM_SERVO_H__
#define __MCPWM_SERVO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "driver/mcpwm.h"

/* Defines -------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  mcpwm_unit_t pwm_unit;
  mcpwm_io_signals_t pwm_signal;    /* only MCPWMxA */
  mcpwm_timer_t pwm_timer;
  int8_t pin_num;
} ServoPulseCfg_t;

typedef struct 
{
  ServoPulseCfg_t pulse_cfg;
} McpwmServo_t;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
int McpwmServo_init(const McpwmServo_t *pCtx);
int McpwmServo_setPulseWidth(const McpwmServo_t *pCtx, uint16_t pulseWidth);

#ifdef __cplusplus
}
#endif

#endif /* __MCPWM_SERVO_H__ */
