/**
 ******************************************************************************
 * @file           WS2812.h
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
#ifndef __WS2812_H__
#define __WS2812_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "led_strip_encoder.h"
#include "driver/rmt_tx.h"

/* Defines -------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef struct 
{
  rmt_tx_channel_config_t rmt_cfg;
  rmt_channel_handle_t rmt_handle;
  rmt_transmit_config_t tx_cfg;
  led_strip_encoder_config_t enc_cfg;
  rmt_encoder_handle_t enc_handle;
} WS2812_dev_t;

typedef struct 
{
  uint8_t g;
  uint8_t r;
  uint8_t b;
} WS2812_pixel_t;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
int WS2812_init(WS2812_dev_t *dev, int gpio_num);
int WS2812_sendPixels(const WS2812_dev_t *dev, WS2812_pixel_t *pixel, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /* __WS2812_H__ */
