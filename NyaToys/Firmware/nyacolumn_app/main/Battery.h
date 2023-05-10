/**
 ******************************************************************************
 * @file           Battery.h
 * @description:   
 * @author:        Hare
 * @date:          2023-01-23
 * @version:       v0.1
 * @history: 
 *    [version]   [date]       [author]       [description]
 *    v0.1   	    2023-01-23   Hare           create
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BATTERY_H__
#define __BATTERY_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Defines -------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  float voltage;
  float voltageMinMax;
  float percent;
  uint8_t isCharging;
} Battery_Info_t;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
int BatteryMonitor_init(void);
Battery_Info_t* BatteryMonitor_getInfo(void);

#ifdef __cplusplus
}
#endif

#endif /* __BATTERY_H__ */
