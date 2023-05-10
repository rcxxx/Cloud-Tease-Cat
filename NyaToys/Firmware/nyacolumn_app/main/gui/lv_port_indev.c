/**
 ******************************************************************************
 * @file           lv_port_indev.c
 * @description:   
 * @author:        Hare
 * @date:          2023-04-02
 * @version:       v0.1
 * @history: 
 *    [version]   [date]       [author]       [description]
 *    v0.1   	    2023-04-02   Hare           create
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
/* Littlevgl specific */
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
#include "lv_port_indev.h"
#include "rotary_encoder_drv.h"

/* Defines -------------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static lv_indev_t *m_indev_encoder;
lv_group_t* indev_group;
/* Private macro -------------------------------------------------------------*/

/* Import function prototypes ------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void encoder_init(void);
static bool encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);

/* Exported functions --------------------------------------------------------*/
void lv_port_indev_init(void)
{
  lv_indev_drv_t indev_drv;

  encoder_init();

  indev_drv.type = LV_INDEV_TYPE_ENCODER;
  indev_drv.read_cb = encoder_read;
  /*Register the driver in LVGL and save the created input device object*/
  m_indev_encoder = lv_indev_drv_register(&indev_drv);

  indev_group = lv_group_create();
  lv_indev_set_group(m_indev_encoder, indev_group);
  // lv_group_set_default(group);
}

/* Private functions ---------------------------------------------------------*/
static void encoder_init(void)
{
  rotary_encoder_init();
}

static bool encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
  data->enc_diff = rotary_encoder_get_diff();  
  data->state = rotary_encoder_get_push_btn() ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
  return false;
}


