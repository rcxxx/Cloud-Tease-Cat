/**
 ******************************************************************************
 * @file           mx113h_motor.h
 * @description:   
 * @author:        Hare
 * @date:          2023-03-03
 * @version:       v0.1
 * @history: 
 *    [version]   [date]       [author]       [description]
 *    v0.1   	    2023-03-03   Hare           create
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MX113H_MOTOR_H__
#define __MX113H_MOTOR_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "driver/ledc.h"

/* Defines -------------------------------------------------------------------*/
// typedef struct
// {
//   int8_t pin_num;
//   uint8_t active_level;
//   uint8_t def_status;
// } MotorPin_t;

typedef struct
{
  ledc_timer_config_t timer_cfg;
  ledc_channel_config_t ch1_cfg;
  ledc_channel_config_t ch2_cfg;
} MotorPWMCfg_t;

typedef struct 
{
  MotorPWMCfg_t pwm_cfg;
  uint8_t dir;
} Mx113hMoter_t;

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
int Mx113hMotor_init(Mx113hMoter_t *pCtx);
int Mx113hMotor_setDir(Mx113hMoter_t *pCtx, uint8_t dir);
int Mx113hMotor_setDuty(const Mx113hMoter_t *pCtx, float duty);

#ifdef __cplusplus
}
#endif

#endif /* __MX113H_MOTOR_H__ */
