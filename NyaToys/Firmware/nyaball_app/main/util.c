/**
 ******************************************************************************
 * @file           util.c
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
#include "util.h"
#include "esp_random.h"
#include "esp_log.h"

/* Defines -------------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Import function prototypes ------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
int random_int_range(int min, int max)
{
  uint32_t rand = esp_random();
  int ret = (rand % (max - min + 1)) + min;

  // ESP_LOGI(__func__, "rand: %ld, result: %d", rand, ret);
  return ret;
}


/* Private functions ---------------------------------------------------------*/
