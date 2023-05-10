/**
 ******************************************************************************
 * @file           rgb_task.c
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
#include "rgb_task.h"
#include "WS2812.h"
#include <string.h>
#include "esp_random.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* Defines -------------------------------------------------------------------*/
#define WS2812_PIN            (5)

/* Private types -------------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static WS2812_dev_t ws2812;
static uint8_t isRunning = 0;

/* Private macro -------------------------------------------------------------*/

/* Import function prototypes ------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void rgb_task(void *pvParameters);

/* Exported functions --------------------------------------------------------*/
void rgb_task_init(void)
{
  isRunning = 1;
  xTaskCreate(rgb_task, "rgb_task", 4096, NULL, 5, NULL);
}

void rgb_task_exit(void)
{
  isRunning = 0;
}

/* Private functions ---------------------------------------------------------*/
static void rgb_task(void *pvParameters)
{
  WS2812_init(&ws2812, WS2812_PIN);

  WS2812_pixel_t pixel;
  memset(&pixel, 0, sizeof(pixel));
  pixel.r = 128;
  WS2812_sendPixels(&ws2812, &pixel, 1);
  vTaskDelay(pdMS_TO_TICKS(1000));

  while (isRunning)
  {
    uint32_t rand_num = esp_random();
    uint8_t *rand_u8_ptr = (uint8_t*)&rand_num;
    pixel.r = rand_u8_ptr[0] & 0xF;
    pixel.g = rand_u8_ptr[1] & 0xF;
    pixel.b = rand_u8_ptr[2] & 0xF;
    WS2812_sendPixels(&ws2812, &pixel, 1);
    vTaskDelay(pdMS_TO_TICKS(100));
  }

  memset(&pixel, 0, sizeof(pixel));
  WS2812_sendPixels(&ws2812, &pixel, 1);
  vTaskDelete(NULL);
}