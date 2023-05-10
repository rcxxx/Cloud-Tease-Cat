/**
 ******************************************************************************
 * @file           MainPage.h
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
#ifndef __MAINPAGE_H__
#define __MAINPAGE_H__

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

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
int MainPage_create(lv_obj_t *par);
int MainPage_update(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAINPAGE_H__ */
