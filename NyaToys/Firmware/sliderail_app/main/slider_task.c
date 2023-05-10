/**
 ******************************************************************************
 * @file           slider_task.c
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
#include "slider_task.h"
#include <string.h>
#include "esp_random.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "McpwmServo.h"
#include "PulseStepper.h"
#include "Limiter.h"
#include "util.h"

/* Defines -------------------------------------------------------------------*/
#define SERVO_PULSE_GPIO      (32)

#define STEPPER1_PIN_EN       (19)
#define STEPPER1_PIN_DIR      (22)
#define STEPPER1_PIN_STP      (21)

#define STEPPER2_PIN_EN       (25)
#define STEPPER2_PIN_DIR      (27)
#define STEPPER2_PIN_STP      (26)

#define STEPMOTOR_MICRO_STEP  (16)

#define LIMIT_SW1_PIN         (13)
#define LIMIT_SW2_PIN         (14)

/* Private types -------------------------------------------------------------*/
typedef enum
{
  SLIDERAIL_STEPPER_IDX_1 = 0,  /*  |  */
  SLIDERAIL_STEPPER_IDX_2,      /* ___ */
  SLIDERAIL_STEPPER_IDX_MAX
} SlideRail_StepperIndex_t;

typedef enum
{
  SLIDERAIL_LIMITER_IDX_1 = 0,  /*  <  */
  SLIDERAIL_LIMITER_IDX_2,      /*  >  */
  SLIDERAIL_LIMITER_IDX_MAX
} SlideRail_LimiterIndex_t;

typedef struct 
{
  uint8_t isEnable;   /* Enable pin is active */
  uint8_t dir;        /* 0 is unknow, 1 is cw direction, 2 is ccw */
  uint8_t isStart;    /* is pulse outputting */
  uint16_t freq;
} SlideRail_StepperStatus_t;

/* Private constants ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static uint8_t isRunning = 0;

static const PulseStepper_t stepper[SLIDERAIL_STEPPER_IDX_MAX] = 
{
  [SLIDERAIL_STEPPER_IDX_1] = 
  {
    {STEPPER1_PIN_EN, 1, 0}, 
    {STEPPER1_PIN_DIR, 1, 0},
    {MCPWM_UNIT_0, MCPWM0A, MCPWM_TIMER_0, 500, STEPPER1_PIN_STP, 0},
  },

  [SLIDERAIL_STEPPER_IDX_2] = 
  {
    {STEPPER2_PIN_EN, 1, 0}, 
    {STEPPER2_PIN_DIR, 1, 0},
    {MCPWM_UNIT_0, MCPWM1A, MCPWM_TIMER_1, 5000, STEPPER2_PIN_STP, 0},
  }
};

static const McpwmServo_t servo[1] = 
{
  [0] = 
  {
    {MCPWM_UNIT_1, MCPWM0A, MCPWM_TIMER_0, SERVO_PULSE_GPIO},
  },
};

static const Limiter_t limiter[SLIDERAIL_LIMITER_IDX_MAX] = 
{
  [SLIDERAIL_LIMITER_IDX_1] = {{LIMIT_SW1_PIN, 1}},
  [SLIDERAIL_LIMITER_IDX_2] = {{LIMIT_SW2_PIN, 1}},
};

static uint8_t trigger_flag = 0;
static uint16_t servo_rand_pulse_width = 0;
SlideRail_StepperStatus_t stepperStatus[SLIDERAIL_STEPPER_IDX_MAX] = {0};

/* Private macro -------------------------------------------------------------*/
#define MOTO1_DIR_FORWARD()               PulseStepper_setDir(&stepper[SLIDERAIL_STEPPER_IDX_1], 0)
#define MOTO1_DIR_REVERSAL()              PulseStepper_setDir(&stepper[SLIDERAIL_STEPPER_IDX_1], 1)

#define MOTO1_OUTPUT_ENABLE()             PulseStepper_setEn(&stepper[SLIDERAIL_STEPPER_IDX_1], 1)
#define MOTO1_OUTPUT_DISABLE()            PulseStepper_setEn(&stepper[SLIDERAIL_STEPPER_IDX_1], 0)

#define MOTO2_DIR_FORWARD()               PulseStepper_setDir(&stepper[SLIDERAIL_STEPPER_IDX_2], 0)
#define MOTO2_DIR_REVERSAL()              PulseStepper_setDir(&stepper[SLIDERAIL_STEPPER_IDX_2], 1)

#define MOTO2_OUTPUT_ENABLE()             PulseStepper_setEn(&stepper[SLIDERAIL_STEPPER_IDX_2], 1)
#define MOTO2_OUTPUT_DISABLE()            PulseStepper_setEn(&stepper[SLIDERAIL_STEPPER_IDX_2], 0)

/* Import function prototypes ------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void slider_task(void *pvParameters);
static uint8_t LimitScan(void);

/* Exported functions --------------------------------------------------------*/
void slider_task_init(void)
{
  isRunning = 1;
  xTaskCreate(slider_task, "slider_task", 4096, NULL, 5, NULL);
}

void slider_task_exit(void)
{
  isRunning = 0;
}

int SlideRailCtrl_getLimiterLStatus(void)
{
  return Limiter_getStatus(&limiter[SLIDERAIL_LIMITER_IDX_1]);
}

int SlideRailCtrl_getLimiterRStatus(void)
{
  return Limiter_getStatus(&limiter[SLIDERAIL_LIMITER_IDX_2]);
}

void slider_ctrl_trigger_random_move(void)
{
  if(!trigger_flag)
    trigger_flag = 1;
}

/* Private functions ---------------------------------------------------------*/
static void slider_ctrl_logic_task(void *pvParameters)
{
  static uint16_t counter = 0;
  static uint16_t counter_target = 0;
  vTaskDelay(pdMS_TO_TICKS(100));

  while (isRunning)
  {
    if(trigger_flag)
    {
      if(counter_target == 0)
      {
        counter_target = random_int_range(20, 50);
      }

      stepperStatus[SLIDERAIL_STEPPER_IDX_2].isStart = 1;
      servo_rand_pulse_width = random_int_range(1000, 2000);

      counter++;
      if(counter > counter_target)
      {
        stepperStatus[SLIDERAIL_STEPPER_IDX_2].isStart = 0;
        counter_target = 0;
        counter = 0;
        trigger_flag = 0;
      }      
    }
    vTaskDelay(pdMS_TO_TICKS(100));
  }
  vTaskDelete(NULL);
}


static void slider_task(void *pvParameters)
{
  int ret = 0;
  McpwmServo_init(&servo[0]);
  /* limiter init */
  for(int i = 0; i < SLIDERAIL_LIMITER_IDX_MAX; i++)
  {
    ret = Limiter_init(&limiter[i]);
    ESP_ERROR_CHECK_WITHOUT_ABORT(ret);
  }

  /* stepper init */
  for(int i = 0; i < SLIDERAIL_STEPPER_IDX_MAX; i++)
  {
    ret = PulseStepper_init(&stepper[i]);
    ESP_ERROR_CHECK_WITHOUT_ABORT(ret);
  }
  
  vTaskDelay(pdMS_TO_TICKS(1000));
  stepperStatus[SLIDERAIL_STEPPER_IDX_1].isEnable = 1;
  stepperStatus[SLIDERAIL_STEPPER_IDX_2].isEnable = 1;
  stepperStatus[SLIDERAIL_STEPPER_IDX_2].freq = 4000;

  xTaskCreate(slider_ctrl_logic_task, "slider_ctrl_logic_task", 4096, NULL, 5, NULL);

  while (isRunning)
  {
    McpwmServo_setPulseWidth(&servo[0], servo_rand_pulse_width);

    if (stepperStatus[SLIDERAIL_STEPPER_IDX_2].isEnable == 1)
    {
      MOTO2_OUTPUT_ENABLE();
    }
    else
    {
      MOTO2_OUTPUT_DISABLE();
    }

    if (stepperStatus[SLIDERAIL_STEPPER_IDX_1].isEnable == 1)
    {
      MOTO1_OUTPUT_ENABLE();
    }
    else
    {
      MOTO1_OUTPUT_DISABLE();
    }


    if(stepperStatus[SLIDERAIL_STEPPER_IDX_1].freq != 0)
    {
      PulseStepper_setPulseFreq(&stepper[SLIDERAIL_STEPPER_IDX_1], stepperStatus[SLIDERAIL_STEPPER_IDX_1].freq);
    }

    if(stepperStatus[SLIDERAIL_STEPPER_IDX_2].freq != 0)
    {
      PulseStepper_setPulseFreq(&stepper[SLIDERAIL_STEPPER_IDX_2], stepperStatus[SLIDERAIL_STEPPER_IDX_2].freq);
    }

    if (stepperStatus[SLIDERAIL_STEPPER_IDX_2].isStart == 1)
    {
      PulseStepper_start(&stepper[SLIDERAIL_STEPPER_IDX_2]);
    }
    else
    {
      PulseStepper_stop(&stepper[SLIDERAIL_STEPPER_IDX_2]);
    }

    if (stepperStatus[SLIDERAIL_STEPPER_IDX_1].isStart == 1)
    {
      PulseStepper_start(&stepper[SLIDERAIL_STEPPER_IDX_1]);
    }
    else
    {
      PulseStepper_stop(&stepper[SLIDERAIL_STEPPER_IDX_1]);
    }

    if (LimitScan() == 1)
    {
      stepperStatus[SLIDERAIL_STEPPER_IDX_2].dir = 2;
    }
    else if (LimitScan() == 2)
    {
      stepperStatus[SLIDERAIL_STEPPER_IDX_2].dir = 1;
    }

    if (stepperStatus[SLIDERAIL_STEPPER_IDX_2].dir == 1)
    {
      MOTO1_DIR_FORWARD();
      MOTO2_DIR_FORWARD();
    }
    else if (stepperStatus[SLIDERAIL_STEPPER_IDX_2].dir == 2)
    {
      MOTO1_DIR_REVERSAL();
      MOTO2_DIR_REVERSAL();
    }

    if (stepperStatus[SLIDERAIL_STEPPER_IDX_1].dir == 1)
    {
      MOTO1_DIR_FORWARD();
      MOTO2_DIR_FORWARD();
    }
    else if (stepperStatus[SLIDERAIL_STEPPER_IDX_1].dir == 2)
    {
      MOTO1_DIR_REVERSAL();
      MOTO2_DIR_REVERSAL();
    }
    
    vTaskDelay(pdMS_TO_TICKS(10));
  }

  vTaskDelete(NULL);
}

static uint8_t LimitScan(void)
{
	if(SlideRailCtrl_getLimiterLStatus() == 1)
	{
		return 1;
	}
	else if(SlideRailCtrl_getLimiterRStatus() == 1)
	{
		return 2;
	}
	
	return 0;
}
