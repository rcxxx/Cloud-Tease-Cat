/**
 ******************************************************************************
 * @file           StatusBar.c
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
#include "StatusBar.h"
#include "SysLog.h"
#include "Battery.h"

/* Defines -------------------------------------------------------------------*/

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
  lv_obj_t* cont;

  struct 
  {
    lv_obj_t * label;
    Battery_Info_t *info;
  } battery;

} ui;

/* Private macro -------------------------------------------------------------*/

/* Import function prototypes ------------------------------------------------*/
LV_FONT_DECLARE(Jcyt_500W_14);

/* Private function prototypes -----------------------------------------------*/
static void BatteryUI_update(void);

/* Exported functions --------------------------------------------------------*/
int StatusBar_create(lv_obj_t *par)
{
  lv_obj_t* cont = lv_obj_create(par, NULL);
  // lv_obj_reset_style_list(cont, LV_OBJ_PART_MAIN); 
  lv_obj_set_size(cont, LV_HOR_RES, STATUS_BAR_HEIGHT);
  ui.cont = cont;

  ui.battery.label = lv_label_create(ui.cont, NULL);
  lv_obj_align(ui.battery.label, NULL, LV_ALIGN_IN_RIGHT_MID, -5, 0);
  lv_label_set_text(ui.battery.label, " ");
  ui.battery.info = BatteryMonitor_getInfo();

  return 0;
}

int StatusBar_update(void)
{
  static uint8_t counter = 0;
  if(counter++ > 10)
  {
    BatteryUI_update();
    counter = 0;
  }
  return 0;
}

/* Private functions ---------------------------------------------------------*/
static void BatteryUI_update(void)
{
  Battery_Info_t *batInfo = ui.battery.info;
  char bat_str[32];
  char tmp_str[32];

  memset(bat_str, 0, sizeof(bat_str));
  strcat(bat_str, " ");
  if(batInfo->isCharging)
  {
    strcat(bat_str, LV_SYMBOL_CHARGE);
    strcat(bat_str, " ");
  }
  
  if(batInfo->percent >= 80)
    strcat(bat_str, LV_SYMBOL_BATTERY_FULL);
  else if(batInfo->percent >= 60)
    strcat(bat_str, LV_SYMBOL_BATTERY_3);
  else if(batInfo->percent >= 40)
    strcat(bat_str, LV_SYMBOL_BATTERY_2);
  else if(batInfo->percent >= 20)
    strcat(bat_str, LV_SYMBOL_BATTERY_1);
  else
    strcat(bat_str, LV_SYMBOL_BATTERY_EMPTY);
  
//  sprintf(tmp_str, " %d%% (%.1fV)", (int)batInfo->percent, batInfo->voltageMinMax);
  sprintf(tmp_str, " %d%%", (int)batInfo->percent);
  strcat(bat_str, tmp_str);

  lv_label_set_text(ui.battery.label, bat_str);
  lv_obj_align(ui.battery.label, NULL, LV_ALIGN_IN_RIGHT_MID, -5, 0);
}

