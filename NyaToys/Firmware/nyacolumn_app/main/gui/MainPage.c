/**
 ******************************************************************************
 * @file           MainPage.c
 * @description:   
 * @author:        Hare
 * @date:          2023-01-24
 * @version:       v0.1
 * @history: 
 *    [version]   [date]       [author]       [description]
 *    v0.1   	    2023-01-24   Hare           create
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "MainPage.h"
#include "StatusBar.h"
#include "step_main.h"

/* Defines -------------------------------------------------------------------*/
#define MAINPAGE_WIDTH        (LV_HOR_RES)
#define MAINPAGE_HEIGHT       (LV_VER_RES - STATUS_BAR_HEIGHT)

/* Private types -------------------------------------------------------------*/
typedef struct
{
  lv_style_t style;
  lv_obj_t* obj;
} ui_obj_t;


/* Private constants ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


static struct
{
  ui_obj_t cont;
  ui_obj_t limiter_l;
  ui_obj_t limiter_r;
  ui_obj_t devname;
  ui_obj_t tease_cat;
  ui_obj_t tease_cat_sw;
} ui;

/* Private macro -------------------------------------------------------------*/

/* Import function prototypes ------------------------------------------------*/
LV_FONT_DECLARE(Jcyt_500W_20);
extern lv_group_t* indev_group;

/* Private function prototypes -----------------------------------------------*/
static void limiter_UIInit(lv_obj_t *par);
static void limiter_UIUpdate(void);
static void TeaseCat_UIInit(lv_obj_t *par);
static void TeaseCat_UIUpdate(void);

/* Exported functions --------------------------------------------------------*/
int MainPage_create(lv_obj_t *par)
{
  lv_obj_t* cont = lv_obj_create(par, NULL);
  lv_style_init(&ui.cont.style);
  // lv_obj_reset_style_list(cont, LV_OBJ_PART_MAIN);
  lv_style_set_border_width(&ui.cont.style, LV_OBJ_PART_MAIN, 0);
  lv_obj_add_style( cont, LV_OBJ_PART_MAIN, &ui.cont.style );
  lv_obj_set_size(cont, MAINPAGE_WIDTH, MAINPAGE_HEIGHT);
  ui.cont.obj = cont;
  lv_obj_align(ui.cont.obj, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);

  TeaseCat_UIInit(cont);
  // lv_style_t *pStyle;
  // pStyle = &ui.devname.style;
  // lv_style_init(pStyle);
  // ui.devname.obj = lv_label_create(cont, NULL);
  // lv_style_set_text_font(pStyle, LV_STATE_DEFAULT, &Jcyt_500W_14);
  // lv_obj_add_style( ui.devname.obj, LV_OBJ_PART_MAIN, pStyle );


  return 0;
}

int MainPage_update(void)
{
  static uint8_t counter = 0;
  if(counter++ > 10)
  {
    TeaseCat_UIUpdate();
    // limiter_UIUpdate();
    counter = 0;
  }
  return 0;
}

/* Private functions ---------------------------------------------------------*/

static void limiter_UIInit(lv_obj_t *par)
{
  uint8_t status = 0;
  lv_obj_t* rect;

  lv_style_t *pStyle = &ui.limiter_l.style;
  lv_style_init(pStyle);
  lv_style_set_bg_opa( pStyle, LV_STATE_DEFAULT, LV_OPA_COVER);
  lv_style_set_bg_color( pStyle, LV_STATE_DEFAULT, lv_color_hex(0xFF0000) );
  lv_style_set_bg_grad_color( pStyle, LV_STATE_DEFAULT, lv_color_hex( 0xFFFFFF ) );
  lv_style_set_bg_grad_dir( pStyle, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR );
  lv_style_set_radius(pStyle, LV_OBJ_PART_MAIN, 0);

  rect = lv_obj_create(par, NULL);
  lv_obj_set_size( rect, 20, MAINPAGE_HEIGHT );
  lv_obj_align(rect, NULL, LV_ALIGN_IN_LEFT_MID, 0, 0);
  lv_obj_reset_style_list(rect, LV_OBJ_PART_MAIN);
  lv_obj_add_style( rect, LV_OBJ_PART_MAIN, pStyle );
  ui.limiter_l.obj = rect;

  pStyle = &ui.limiter_r.style;
  lv_style_init(pStyle);
  lv_style_set_bg_opa( pStyle, LV_STATE_DEFAULT, LV_OPA_COVER);
  lv_style_set_bg_color( pStyle, LV_STATE_DEFAULT, lv_color_hex(0xFFFFFF) );
  lv_style_set_bg_grad_color( pStyle, LV_STATE_DEFAULT, lv_color_hex( 0xFF0000 ) );
  lv_style_set_bg_grad_dir( pStyle, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR );
  lv_style_set_radius(pStyle, LV_OBJ_PART_MAIN, 0);

  rect = lv_obj_create(par, NULL);
  lv_obj_set_size( rect, 20, MAINPAGE_HEIGHT );
  lv_obj_align(rect, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 0);
  lv_obj_reset_style_list(rect, LV_OBJ_PART_MAIN);
  lv_obj_add_style( rect, LV_OBJ_PART_MAIN, pStyle );
  ui.limiter_r.obj = rect;

}

static void limiter_UIUpdate(void)
{
  uint8_t status = 0;

  status = ! SlideRailCtrl_getLimiterLStatus();
  lv_obj_set_hidden(ui.limiter_l.obj, status);

  status = ! SlideRailCtrl_getLimiterRStatus();
  lv_obj_set_hidden(ui.limiter_r.obj, status);

}

static void TeaseCat_UIInit(lv_obj_t *par)
{
  lv_style_t *pStyle;
  pStyle = &ui.tease_cat.style;
  lv_style_init(pStyle);
  ui.tease_cat.obj = lv_label_create(par, NULL);
  lv_style_set_text_font(pStyle, LV_STATE_DEFAULT, &Jcyt_500W_20);
  lv_obj_add_style( ui.tease_cat.obj, LV_OBJ_PART_MAIN, pStyle );
  lv_obj_align(ui.tease_cat.obj, NULL, LV_ALIGN_IN_LEFT_MID, 10, 0);
  // lv_label_set_text(ui.tease_cat.obj, "远程逗猫");
  ui.tease_cat_sw.obj = lv_switch_create(par, NULL);
  lv_obj_align(ui.tease_cat_sw.obj, ui.tease_cat.obj, LV_ALIGN_OUT_RIGHT_MID, 40, 0);

}

static void TeaseCat_UIUpdate(void)
{
  if(step_task_get_status_auto())
  {
    lv_label_set_text(ui.tease_cat.obj, "自动逗猫");
    lv_switch_on(ui.tease_cat_sw.obj, LV_ANIM_ON);
  }
  else
  {
    lv_label_set_text(ui.tease_cat.obj, "远程逗猫");
    lv_switch_off(ui.tease_cat_sw.obj, LV_ANIM_ON);
  }
}
