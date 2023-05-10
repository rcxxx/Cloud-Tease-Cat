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
#include "RPCProtocol_ll_esp32now.h"
#include "RPCProtocol_ll_esp32uart.h"
#include "driver/uart.h"
#include <driver/gpio.h>
#include "nvs_flash.h"
#include "nvs.h"

/* Defines -------------------------------------------------------------------*/
#define TAG  "main"

/* Private types -------------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Import function prototypes ------------------------------------------------*/
// extern uint8_t RPCProtocol_DevID;
static void changeUart0Pin(uint8_t tx_pin, uint8_t rx_pin);

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

  /* UART Pin change */
  changeUart0Pin(14, 15);
  // RPCProtocol_DevID = 0;
  RPCProtocol_ESP32Now_init();
  RPCProtocol_ESP32UART_init();

  while (1)
  {
    vTaskDelay(pdMS_TO_TICKS(10));
  }
  
}

/* Private functions ---------------------------------------------------------*/
static void changeUart0Pin(uint8_t tx_pin, uint8_t rx_pin)
{
  gpio_reset_pin(tx_pin);
  gpio_reset_pin(rx_pin);
  uart_set_pin(UART_NUM_0, tx_pin, rx_pin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}

