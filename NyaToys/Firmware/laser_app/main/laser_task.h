/**
 ******************************************************************************
 * @file           laser_task.h
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
#ifndef __LASER_TASK_H__
#define __LASER_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void laser_task_init(void);
void laser_task_exit(void);
void laser_task_trigger_random_move(void);

#ifdef __cplusplus
}
#endif

#endif /* __LASER_TASK_H__ */
