/**
 ******************************************************************************
 * @file           main.c
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
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "RPCProtocol_ll_esp32now.h"
#include "gui_task.h"
#include "Battery.h"
#include "step_main.h"
#include "disp_driver.h"
#include "rotary_encoder_drv.h"

/* Defines -------------------------------------------------------------------*/
#define TAG  "main"

#define PWRKEEP_PIN           (15)
#define PWR_BTN_PIN           (35)


/* Private types -------------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Import function prototypes ------------------------------------------------*/
extern uint8_t RPCProtocol_DevID;

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void app_main(void)
{
  int err = 0;

  /* output pin */
  gpio_config_t io_conf;
  io_conf.intr_type = GPIO_INTR_DISABLE;
  io_conf.mode = GPIO_MODE_OUTPUT;
  io_conf.pull_down_en = 0;
  io_conf.pull_up_en = 0;

  io_conf.pin_bit_mask = BIT64(PWRKEEP_PIN);
  ESP_ERROR_CHECK(gpio_config(&io_conf));
  ESP_ERROR_CHECK(gpio_set_level(PWRKEEP_PIN, 1));

  /* input pin */
  io_conf.mode = GPIO_MODE_INPUT;

  io_conf.pin_bit_mask = BIT64(PWR_BTN_PIN);
  ESP_ERROR_CHECK(gpio_config(&io_conf));

  err = nvs_flash_init();
  if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    // NVS partition was truncated and needs to be erased
    // Retry nvs_flash_init
    ESP_ERROR_CHECK(nvs_flash_erase());
    err = nvs_flash_init();
  }
  ESP_ERROR_CHECK( err );

  BatteryMonitor_init();

  step_task_init();

  RPCProtocol_DevID = 10;
  RPCProtocol_ESP32Now_init();

  GuiTask_create();

  while (gpio_get_level(PWR_BTN_PIN) == 0)
  {
    vTaskDelay(pdMS_TO_TICKS(10));
  }

  while (1)
  {
    if(gpio_get_level(PWR_BTN_PIN) == 0)
    {
      uint8_t counter = 0;
      uint8_t power_down_flag = 0;
      while(gpio_get_level(PWR_BTN_PIN) == 0)
      {
        vTaskDelay(pdMS_TO_TICKS(10));
        counter++;
        if(counter > 100)
        {
          if(gpio_get_level(PWR_BTN_PIN) == 0)
          {
            ESP_LOGI(TAG, ">>> Power down");
            st7789_enable_backlight(0);
            gpio_set_level(PWRKEEP_PIN, 0);
          }
          power_down_flag = 1;
          counter = 0;
        }
      }
      
      if(!power_down_flag)
      {
        step_task_set_status_auto(!step_task_get_status_auto());
      }

    }
    
    vTaskDelay(pdMS_TO_TICKS(10));
  }
  
}

/* Private functions ---------------------------------------------------------*/


