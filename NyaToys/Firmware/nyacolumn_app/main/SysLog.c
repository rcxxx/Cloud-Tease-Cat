/**
 ******************************************************************************
 * @file           syslog.c
 * @description:   
 * @author:        Hare
 * @date:          2022-02-05
 * @version:       v0.1
 * @history: 
 *    [version]   [date]       [author]       [description]
 *    v0.1   	    2022-02-05   Hare           create
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "SysLog.h"
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#if defined __DEV_STM32__
#include "SEGGER_RTT.h"
#elif defined __DEV_PCQT__
#include <stdio.h>
#elif defined CONFIG_IDF_TARGET_ESP32 || defined CONFIG_IDF_TARGET_ESP32C3
#include "esp_log.h"
#include "esp_system.h"
#endif
/* Defines -------------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
const char LogLevelStr[SYSLOG_MAX] = 
{
  ' ',
  'E',
  'W',
  'I',
  'D',
  'V',
};
/* Private macro -------------------------------------------------------------*/

/* Import function prototypes ------------------------------------------------*/
#if defined __DEV_STM32__
extern int SEGGER_RTT_vprintf(unsigned BufferIndex, const char * sFormat, va_list * pParamList);
#endif
/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void SysLog_write(SysLog_Level_t level, const char* tag, const char *format, ...)
{
  va_list list;

  if(level >= SYSLOG_MAX)
  {
    return;
  }

  if(NULL == tag)
  {
    tag = "";
  }

  va_start(list, format);
  
#if defined __DEV_STM32__
  SEGGER_RTT_printf(0, "[%c] %s: \t", LogLevelStr[level], tag);
  SEGGER_RTT_vprintf(0, format, &list);
#elif defined __DEV_PCQT__
  printf("[%c] %s: \t", LogLevelStr[level], tag);
  vprintf(format, list);
  printf("\n");
  fflush(stdout);
#endif

  va_end(list);
}
/* Private functions ---------------------------------------------------------*/

