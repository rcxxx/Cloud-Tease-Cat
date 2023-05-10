/**
 ******************************************************************************
 * @file           laser_task.c
 * @description:
 * @author:        Hare
 * @date:          2023-03-04
 * @version:       v0.1
 * @history:
 *    [version]   [date]       [author]       [description]
 *    v0.1   	    2023-03-04   Hare           create
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "laser_task.h"
#include <string.h>
#include "util.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "SysLog.h"

/* Defines -------------------------------------------------------------------*/
#define LASER_PWR_TRIG_PIN           (1)

/* Private types -------------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static uint8_t trigger_flag = 0;

/* Private macro -------------------------------------------------------------*/

/* Import function prototypes ------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void laser_task(void *pvParameters);
static uint8_t isRunning = 0;

/* Exported functions --------------------------------------------------------*/
void laser_task_init(void)
{
  isRunning = 1;
  xTaskCreate(laser_task, "laser_task", 4096, NULL, 5, NULL);
}

void laser_task_exit(void)
{
  isRunning = 0;
}

void laser_task_trigger_random_move(void)
{
  if(!trigger_flag)
    trigger_flag = 1;
}

/* Private functions ---------------------------------------------------------*/
void pwr_trigger()
{
  gpio_set_level(LASER_PWR_TRIG_PIN, 1);
  vTaskDelay(pdMS_TO_TICKS(100));
  gpio_set_level(LASER_PWR_TRIG_PIN, 0);
  vTaskDelay(pdMS_TO_TICKS(100));
}

static void laser_task(void *pvParameters)
{
  /* output pin */
  gpio_config_t io_conf;
  io_conf.intr_type = GPIO_INTR_DISABLE;
  io_conf.mode = GPIO_MODE_OUTPUT;
  io_conf.pull_down_en = 0;
  io_conf.pull_up_en = 0;

  io_conf.pin_bit_mask = BIT64(LASER_PWR_TRIG_PIN);
  ESP_ERROR_CHECK(gpio_config(&io_conf));
  ESP_ERROR_CHECK(gpio_set_level(LASER_PWR_TRIG_PIN, 0));

  while (isRunning)
  {
    if(trigger_flag)
    {
      uint16_t time = random_int_range(3000, 10000);

      SYS_LOGI(__func__, "trig, time: %d", time);

      pwr_trigger();
      vTaskDelay(pdMS_TO_TICKS(time));
      pwr_trigger();

      /* stop wait */
      vTaskDelay(pdMS_TO_TICKS(500));
      trigger_flag = 0;
    }
    vTaskDelay(pdMS_TO_TICKS(100));
  }

  vTaskDelete(NULL);
}




