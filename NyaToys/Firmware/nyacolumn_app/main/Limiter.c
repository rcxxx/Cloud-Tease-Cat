/**
 ******************************************************************************
 * @file           Limiter.c
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
#include "Limiter.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/gpio.h"

/* Defines -------------------------------------------------------------------*/
#define TAG     "Limiter"

/* Private types -------------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
#define PIN_ACTIVE2LEVEL(pin, status) (status ? pin.active_level:!(pin.active_level))
#define PIN_LEVEL2ACTIVE(pin, level) ((level == pin.active_level)? 1:0)

/* Import function prototypes ------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
int Limiter_init(const Limiter_t *pCtx)
{
  int ret = 0;
  if(pCtx == NULL)
  {
    return ESP_ERR_INVALID_ARG;
  }

  /* gpio init */
  gpio_config_t io_conf;
  io_conf.intr_type = GPIO_INTR_DISABLE;
  io_conf.mode = GPIO_MODE_INPUT;
  //bit mask of the pins that you want to set
  io_conf.pin_bit_mask = (BIT64(pCtx->pin.pin_num));
  io_conf.pull_down_en = 0;
  io_conf.pull_up_en = 0;

  ret = gpio_config(&io_conf);
  ESP_ERROR_CHECK_WITHOUT_ABORT(ret);

  return ret;
}

int Limiter_getStatus(const Limiter_t *pCtx)
{
  int ret = 0;
  ret = gpio_get_level(pCtx->pin.pin_num);
  // ESP_LOGI(TAG, "Pin:%d, level:%d", pCtx->pin.pin_num, ret);
  return PIN_LEVEL2ACTIVE(pCtx->pin, ret);
}


/* Private functions ---------------------------------------------------------*/
