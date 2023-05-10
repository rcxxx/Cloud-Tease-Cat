/**
 ******************************************************************************
 * @file           gui_task.h
 * @description:   
 * @author:        Hare
 * @date:          2023-01-19
 * @version:       v0.1
 * @history: 
 *    [version]   [date]       [author]       [description]
 *    v0.1   	    2023-01-19   Hare           create
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GUI_TASK_H__
#define __GUI_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
int GuiTask_create(void);
int GuiTask_destroy(void);


#ifdef __cplusplus
}
#endif

#endif /* __GUI_TASK_H__ */
