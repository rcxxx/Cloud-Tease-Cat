/**
 ******************************************************************************
 * @file           syslog.h
 * @description:   
 * @author:        Hare
 * @date:          2022-02-05
 * @version:       v0.1
 * @history: 
 *    [version]   [date]       [author]       [description]
 *    v0.1   	    2022-02-05   Hare           create
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYSLOG_H__
#define __SYSLOG_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#if defined CONFIG_IDF_TARGET_ESP32 || defined CONFIG_IDF_TARGET_ESP32C3
#include "esp_log.h"
#endif

/* Defines -------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  SYSLOG_NONE = 0,
  SYSLOG_ERROR,
  SYSLOG_WARN,
  SYSLOG_INFO,
  SYSLOG_DEBUG,
  SYSLOG_VERBOSE,
  SYSLOG_MAX,
} SysLog_Level_t;
/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#if defined CONFIG_IDF_TARGET_ESP32 || defined CONFIG_IDF_TARGET_ESP32C3
#define SYS_LOGE( tag, format, ... ) ESP_LOGE(tag, format, ##__VA_ARGS__)
#define SYS_LOGW( tag, format, ... ) ESP_LOGW(tag, format, ##__VA_ARGS__)
#define SYS_LOGI( tag, format, ... ) ESP_LOGI(tag, format, ##__VA_ARGS__)
#define SYS_LOGD( tag, format, ... ) ESP_LOGD(tag, format, ##__VA_ARGS__)
#define SYS_LOGV( tag, format, ... ) ESP_LOGV(tag, format, ##__VA_ARGS__)
#else
#define SYS_LOGE( tag, format, ... ) SysLog_write(SYSLOG_ERROR,   tag, format, ##__VA_ARGS__)
#define SYS_LOGW( tag, format, ... ) SysLog_write(SYSLOG_WARN,    tag, format, ##__VA_ARGS__)
#define SYS_LOGI( tag, format, ... ) SysLog_write(SYSLOG_INFO,    tag, format, ##__VA_ARGS__)
#define SYS_LOGD( tag, format, ... ) SysLog_write(SYSLOG_DEBUG,   tag, format, ##__VA_ARGS__)
#define SYS_LOGV( tag, format, ... ) SysLog_write(SYSLOG_VERBOSE, tag, format, ##__VA_ARGS__)
#endif

#if defined __DEV_PCQT__
#define QSTRING2CHARS(x)             (x.toLatin1().data())
#endif

/* Exported functions --------------------------------------------------------*/

void SysLog_write(SysLog_Level_t level, const char* tag, const char *format, ...);


#ifdef __cplusplus
}
#endif

#endif /* __SYSLOG_H__ */
