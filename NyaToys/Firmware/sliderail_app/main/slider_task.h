/**
 ******************************************************************************
 * @file           slider_task.h
 * @description:   
 * @author:        Hare
 * @date:          2023-03-04
 * @version:       v0.1
 * @history: 
 *    [version]   [date]       [author]       [description]
 *    v0.1   	    2023-03-04   Hare           create
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SLIDER_TASK_H__
#define __SLIDER_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void slider_task_init(void);
void slider_task_exit(void);
void slider_ctrl_trigger_random_move(void);

int SlideRailCtrl_getLimiterLStatus(void);
int SlideRailCtrl_getLimiterRStatus(void);

#ifdef __cplusplus
}
#endif

#endif /* __SLIDER_TASK_H__ */
