/**
 ******************************************************************************
 * @file           rotary_encoder_drv.h
 * @description:   
 * @author:        Hare
 * @date:          2023-04-02
 * @version:       v0.1
 * @history: 
 *    [version]   [date]       [author]       [description]
 *    v0.1   	    2023-04-02   Hare           create
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ROTARY_ENCODER_DRV_H__
#define __ROTARY_ENCODER_DRV_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void rotary_encoder_init(void);
int rotary_encoder_get_diff(void);
int rotary_encoder_get_push_btn(void);

#ifdef __cplusplus
}
#endif

#endif /* __ROTARY_ENCODER_DRV_H__ */
