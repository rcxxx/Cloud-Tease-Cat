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
#include "rgb_task.h"
#include "laser_task.h"
#include "RPCProtocol_ll_esp32now.h"


/* Defines -------------------------------------------------------------------*/
#define TAG  "main"

#define PWR_BTN_PIN           (0)


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


  err = nvs_flash_init();
  if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    // NVS partition was truncated and needs to be erased
    // Retry nvs_flash_init
    ESP_ERROR_CHECK(nvs_flash_erase());
    err = nvs_flash_init();
  }
  ESP_ERROR_CHECK( err );

  RPCProtocol_DevID = 5;
  RPCProtocol_ESP32Now_init();

  rgb_task_init();
  laser_task_init();

  while (1)
  {
    vTaskDelay(pdMS_TO_TICKS(10));
  }
  
}

/* Private functions ---------------------------------------------------------*/


