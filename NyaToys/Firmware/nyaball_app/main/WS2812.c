/**
 ******************************************************************************
 * @file           WS2812.c
 * @description:   
 * @author:        Hare
 * @date:          2023-03-04
 * @version:       v0.1
 * @history: 
 *    [version]   [date]       [author]       [description]
 *    v0.1   	    2023-03-04   Hare           create
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "WS2812.h"

/* Defines -------------------------------------------------------------------*/
#define RMT_LED_STRIP_RESOLUTION_HZ 10000000 // 10MHz resolution, 1 tick = 0.1us (led strip needs a high resolution)

/* Private types -------------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Import function prototypes ------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
int WS2812_init(WS2812_dev_t *dev, int gpio_num)
{
  int ret = 0;
  if(dev == NULL)
  {
    return ESP_ERR_INVALID_ARG;
  }

  dev->rmt_cfg.clk_src = RMT_CLK_SRC_DEFAULT; // select source clock
  dev->rmt_cfg.gpio_num = gpio_num;
  dev->rmt_cfg.mem_block_symbols = 64; // increase the block size can make the LED less flickering
  dev->rmt_cfg.resolution_hz = RMT_LED_STRIP_RESOLUTION_HZ;
  dev->rmt_cfg.trans_queue_depth = 4; // set the number of transactions that can be pending in the background

  ret = rmt_new_tx_channel(&dev->rmt_cfg, &dev->rmt_handle);
  ESP_ERROR_CHECK_WITHOUT_ABORT(ret);

  dev->enc_cfg.resolution = dev->rmt_cfg.resolution_hz,
  ret = rmt_new_led_strip_encoder(&dev->enc_cfg, &dev->enc_handle);
  ESP_ERROR_CHECK_WITHOUT_ABORT(ret);

  ret = rmt_enable(dev->rmt_handle);
  ESP_ERROR_CHECK_WITHOUT_ABORT(ret);

  dev->tx_cfg.loop_count = 0;

  return ret;
}

int WS2812_sendPixels(const WS2812_dev_t *dev, WS2812_pixel_t *pixel, uint32_t size)
{
  int ret = 0;
  ret = rmt_transmit(dev->rmt_handle, dev->enc_handle, pixel, (sizeof(WS2812_pixel_t) * size), &dev->tx_cfg);
  return ret;
}

/* Private functions ---------------------------------------------------------*/
