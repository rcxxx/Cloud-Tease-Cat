/**
 ******************************************************************************
 * @file           StatusBar.h
 * @description:   
 * @author:        Hare
 * @date:          2023-01-24
 * @version:       v0.1
 * @history: 
 *    [version]   [date]       [author]       [description]
 *    v0.1   	    2023-01-24   Hare           create
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STATUSBAR_H__
#define __STATUSBAR_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Littlevgl specific */
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

/* Defines -------------------------------------------------------------------*/
#define STATUS_BAR_HEIGHT 25

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
int StatusBar_create(lv_obj_t *par);
int StatusBar_update(void);

#ifdef __cplusplus
}
#endif

#endif /* __STATUSBAR_H__ */
