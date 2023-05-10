/**
 ******************************************************************************
 * @file           rpc_cmd_cb.c
 * @description:   
 * @author:        Hare
 * @date:          2022-09-25
 * @version:       v0.1
 * @history: 
 *    [version]   [date]       [author]       [description]
 *    v0.1   	    2022-09-25   Hare           create
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "rpc_cmd_cb.h"
#include <errno.h>
#include <string.h>
#include "RPCProtocol_cfg.h"
#include "SysLog.h"
#if defined CONFIG_IDF_TARGET_ESP32 || defined CONFIG_IDF_TARGET_ESP32C3
#include "motor_task.h"
// #include "RPCProtocol_ll_esp32now.h"
// #include "RPCProtocol_ll_esp32uart.h"
// #include "SplitterLogic.h"
// #include "SplitterLLCtrl.h"
// #include "ota.h"
// #include "esp_system.h"
#elif defined __DEV_PCQT__
//#include "RPCProtocol_ll_qtSerialHelper.h"
// #include "splitter_if_c.h"
#endif

/* Defines -------------------------------------------------------------------*/
#define TAG   "CSGS_CMD"
/* Private types -------------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Import function prototypes ------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void RPCCMD_triggerRandomMove_cb(uint8_t *pData, uint16_t size)
{
  if(size == sizeof(RPCProtocol_DummyData_t))
  {
    motor_task_trigger_random_move();
  }
  else
  {
    /* size not match */
  }
}



/* Private functions ---------------------------------------------------------*/
