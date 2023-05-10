/**
 ******************************************************************************
 * @file           mx113h_motor.c
 * @description:   
 * @author:        Hare
 * @date:          2023-03-03
 * @version:       v0.1
 * @history: 
 *    [version]   [date]       [author]       [description]
 *    v0.1   	    2023-03-03   Hare           create
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "mx113h_motor.h"

/* Defines -------------------------------------------------------------------*/


/* Private types -------------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Import function prototypes ------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static uint32_t Mx113hMotor_geInvtDuty(const Mx113hMoter_t *pCtx, uint32_t duty);

/* Exported functions --------------------------------------------------------*/
int Mx113hMotor_init(Mx113hMoter_t *pCtx)
{
  int ret = 0;
  if(pCtx == NULL)
  {
    return ESP_ERR_INVALID_ARG;
  }

  ret = ledc_timer_config(&pCtx->pwm_cfg.timer_cfg);
  ESP_ERROR_CHECK_WITHOUT_ABORT(ret);

  ret = ledc_channel_config(&pCtx->pwm_cfg.ch1_cfg);
  ESP_ERROR_CHECK_WITHOUT_ABORT(ret);

  ret = ledc_channel_config(&pCtx->pwm_cfg.ch2_cfg);
  ESP_ERROR_CHECK_WITHOUT_ABORT(ret);

  Mx113hMotor_setDir(pCtx, 0);
  Mx113hMotor_setDuty(pCtx, 0);

  return ret;
}

int Mx113hMotor_setDir(Mx113hMoter_t *pCtx, uint8_t dir)
{
  int ret = 0;
  uint32_t duty = 0;
  ledc_channel_config_t *ch_out;
  ledc_channel_config_t *ch_stop;

  if(pCtx == NULL)
  {
    return ESP_ERR_INVALID_ARG;
  }

  if(dir)
  {
    pCtx->dir = 1;
    ch_out = &pCtx->pwm_cfg.ch2_cfg;
    ch_stop = &pCtx->pwm_cfg.ch1_cfg;
  }
  else
  {
    pCtx->dir = 0;
    ch_out = &pCtx->pwm_cfg.ch1_cfg;
    ch_stop = &pCtx->pwm_cfg.ch2_cfg;
  }
  
  duty = ledc_get_duty(ch_stop->speed_mode, ch_stop->channel);
    
  ret = ledc_set_duty(ch_stop->speed_mode, ch_stop->channel, Mx113hMotor_geInvtDuty(pCtx, 0));
  // ret = ledc_set_duty(ch_stop->speed_mode, ch_stop->channel, 0);
  ESP_ERROR_CHECK_WITHOUT_ABORT(ret);
  ret = ledc_set_duty(ch_out->speed_mode, ch_out->channel, duty);
  ESP_ERROR_CHECK_WITHOUT_ABORT(ret);

  ret = ledc_update_duty(ch_stop->speed_mode, ch_stop->channel);
  ESP_ERROR_CHECK_WITHOUT_ABORT(ret);
  ret = ledc_update_duty(ch_out->speed_mode, ch_out->channel);
  ESP_ERROR_CHECK_WITHOUT_ABORT(ret);

  return ret;
}

int Mx113hMotor_setDuty(const Mx113hMoter_t *pCtx, float duty)
{
  int ret = 0;
  uint32_t set_duty = 0;

  const ledc_channel_config_t *ch_out;

  if(pCtx == NULL)
  {
    return ESP_ERR_INVALID_ARG;
  }

  if(pCtx->dir)
  {
    ch_out = &pCtx->pwm_cfg.ch2_cfg;
  }
  else
  {
    ch_out = &pCtx->pwm_cfg.ch1_cfg;
  }

  set_duty = ((1 << pCtx->pwm_cfg.timer_cfg.duty_resolution) - 1) * duty / 100;

  set_duty = Mx113hMotor_geInvtDuty(pCtx, set_duty);
  
  ret = ledc_set_duty(ch_out->speed_mode, ch_out->channel, set_duty);
  ESP_ERROR_CHECK_WITHOUT_ABORT(ret);

  ret = ledc_update_duty(ch_out->speed_mode, ch_out->channel);
  ESP_ERROR_CHECK_WITHOUT_ABORT(ret);
  
  return ret;
}

/* Private functions ---------------------------------------------------------*/
static uint32_t Mx113hMotor_geInvtDuty(const Mx113hMoter_t *pCtx, uint32_t duty)
{
  uint32_t duty_max = ((1 << pCtx->pwm_cfg.timer_cfg.duty_resolution) - 1);
  return duty_max - duty;
}
