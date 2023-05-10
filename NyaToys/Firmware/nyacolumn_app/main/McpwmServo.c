/**
 ******************************************************************************
 * @file           McpwmServo.c
 * @description:   
 * @author:        Hare
 * @date:          2023-01-21
 * @version:       v0.1
 * @history: 
 *    [version]   [date]       [author]       [description]
 *    v0.1   	    2023-01-21   Hare           create
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "McpwmServo.h"
#include "esp_system.h"
#include "esp_log.h"

/* Defines -------------------------------------------------------------------*/
#define TAG     "McpwmServo"

#define SERVO_MIN_PULSEWIDTH_US (1000) // Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH_US (2000) // Maximum pulse width in microsecond

/* Private types -------------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Import function prototypes ------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
int McpwmServo_init(const McpwmServo_t *pCtx)
{
  int ret = 0;
  if(pCtx == NULL)
  {
    return ESP_ERR_INVALID_ARG;
  }

  /* pwm init */
  ret = mcpwm_gpio_init(pCtx->pulse_cfg.pwm_unit, pCtx->pulse_cfg.pwm_signal, pCtx->pulse_cfg.pin_num);
  ESP_ERROR_CHECK_WITHOUT_ABORT(ret);

  mcpwm_config_t pwm_config = {
      .frequency = 50,
      .cmpr_a = 0,     // duty cycle of PWMxA = 0
      .cmpr_b = 0,
      .counter_mode = MCPWM_UP_COUNTER,
      .duty_mode = MCPWM_DUTY_MODE_0,
  };

  ret = mcpwm_init(pCtx->pulse_cfg.pwm_unit, pCtx->pulse_cfg.pwm_timer, &pwm_config);
  ESP_ERROR_CHECK_WITHOUT_ABORT(ret);

  return ret;
}

int McpwmServo_setPulseWidth(const McpwmServo_t *pCtx, uint16_t pulseWidth)
{
  int ret = 0;
  
  if(pulseWidth == 0) {}
  else if(pulseWidth < SERVO_MIN_PULSEWIDTH_US) { pulseWidth = SERVO_MIN_PULSEWIDTH_US; }
  else if(pulseWidth > SERVO_MAX_PULSEWIDTH_US) { pulseWidth = SERVO_MAX_PULSEWIDTH_US; }

  ret = mcpwm_set_duty_in_us(pCtx->pulse_cfg.pwm_unit, pCtx->pulse_cfg.pwm_timer, MCPWM_GEN_A, pulseWidth);
  ESP_ERROR_CHECK_WITHOUT_ABORT(ret);
  return ret;
}


/* Private functions ---------------------------------------------------------*/
