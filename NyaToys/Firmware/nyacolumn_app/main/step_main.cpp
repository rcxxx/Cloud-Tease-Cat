#include <stdio.h>
#include "DendoStepper.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "step_main.h"
#include "Limiter.h"
#include "McpwmServo.h"
#include "util.h"

#define STEPPER1_PIN_EN       (19)
#define STEPPER1_PIN_DIR      (22)
#define STEPPER1_PIN_STP      (21)

#define STEPPER2_PIN_EN       (25)
#define STEPPER2_PIN_DIR      (27)
#define STEPPER2_PIN_STP      (26)

#define LIMIT_SW1_PIN         (13)
#define LIMIT_SW2_PIN         (14)

// #define SERVO_PULSE_GPIO      (32)
#define SERVO_PULSE_GPIO      (STEPPER2_PIN_EN)

typedef enum
{
  SLIDERAIL_LIMITER_IDX_1 = 0,  /*  <  */
  SLIDERAIL_LIMITER_IDX_2,      /*  >  */
  SLIDERAIL_LIMITER_IDX_MAX
} SlideRail_LimiterIndex_t;

DendoStepper StepperYaw;
DendoStepper StepperX;

static uint8_t isRunning = 0;
static uint8_t isYawTrigger = 0;
static uint8_t isServoTrigger = 0;
static uint8_t YawMode = 0;

static uint8_t isFindCatEnable = 0;
static uint8_t isTeaseCatEnable = 0;
static uint8_t isTeaseCatAuto = 0;

static const Limiter_t limiter[SLIDERAIL_LIMITER_IDX_MAX] = 
{
  [SLIDERAIL_LIMITER_IDX_1] = {{LIMIT_SW1_PIN, 1}},
  [SLIDERAIL_LIMITER_IDX_2] = {{LIMIT_SW2_PIN, 1}},
};

static const McpwmServo_t servo[1] = 
{
  [0] = 
  {
    {MCPWM_UNIT_1, MCPWM0A, MCPWM_TIMER_0, SERVO_PULSE_GPIO},
  },
};

static void step_yaw_task(void *pvParameters);
static void step_x_task(void *pvParameters);
static void servo_task(void *pvParameters);
static void step_logic_task(void *pvParameters);

void step_task_init(void)
{
  isRunning = 1;
  xTaskCreate(step_yaw_task, "step_yaw_task", 4096, NULL, 5, NULL);
  xTaskCreate(servo_task, "servo_task", 4096, NULL, 5, NULL);
  xTaskCreate(step_logic_task, "step_logic_task", 4096, NULL, 5, NULL);
}

void step_task_trigger_find_cat(void)
{
    isFindCatEnable = 1;
    isTeaseCatEnable = 0;
}

void step_task_trigger_tease_cat(void)
{
    isFindCatEnable = 0;
    isTeaseCatEnable = 1;
}

void step_task_trigger_stop(void)
{
    isFindCatEnable = 0;
    isTeaseCatEnable = 0;
}

uint8_t step_task_get_status_auto(void)
{
    return isTeaseCatAuto;
}

void step_task_set_status_auto(uint8_t is_auto)
{
    isTeaseCatAuto = is_auto;
}

void step_trigger_yaw_random_move(void)
{
  if(!isYawTrigger)
  {
    YawMode = random_int_range(0, 1);
    isYawTrigger = 1;
  }
}

void step_trigger_servo_random_move(void)
{
  if(!isServoTrigger)
    isServoTrigger = 1;
}

static void stepSetPosWait(DendoStepper &mStepper, int32_t relative)
{
    mStepper.runPos(relative);
    while (mStepper.getState() != DISABLED && mStepper.getState() !=IDLE)
    {
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

int SlideRailCtrl_getLimiterLStatus(void)
{
  return Limiter_getStatus(&limiter[SLIDERAIL_LIMITER_IDX_1]);
}

int SlideRailCtrl_getLimiterRStatus(void)
{
  return Limiter_getStatus(&limiter[SLIDERAIL_LIMITER_IDX_2]);
}

static void mode_0(uint8_t cnt)
{
    for (size_t i = 0; i < cnt; i++)
    {
        uint16_t step = random_int_range(2000, 20000);
        uint16_t step_speed = random_int_range(2000, 5000);
        int8_t step_dir = random_int_range(0, 1);
        if(step_dir == 0)
        {
            step_dir = -1;
        }
        StepperYaw.setSpeed(step_speed, 800, 800);
        stepSetPosWait(StepperYaw, step_dir*step);
    }
    
}

static void step_yaw_task(void *pvParameters)
{
    DendoStepper_config_t step_cfg = {
        .stepPin = STEPPER1_PIN_STP,
        .dirPin = STEPPER1_PIN_DIR,
        .enPin = STEPPER1_PIN_EN,
        .timer_group = TIMER_GROUP_1,
        .timer_idx = TIMER_0,
        .miStep = MICROSTEP_16,
        .stepAngle = 1.8
    };

    StepperYaw.config(&step_cfg);

    StepperYaw.init();

    vTaskDelay(pdMS_TO_TICKS(1000));

    // step_trigger_random_move();

    while (isRunning)
    {
        if(isYawTrigger)
        {
            switch(YawMode)
            {
                case 0:
                {
                    mode_0(3);
                }
                break;
                default:
                    vTaskDelay(pdMS_TO_TICKS(10));
                break;

            }
            isYawTrigger = 0;
        }
        else
        {
            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }
}

static void servo_task(void *pvParameters)
{
    static uint16_t counter = 0;
    static uint16_t counter_target = 0;
    static uint16_t servo_rand_pulse_width = 0;

    McpwmServo_init(&servo[0]);

    while (1)
    {
        if(isServoTrigger)
        {
            if(counter_target == 0)
            {
                counter_target = random_int_range(20, 50);
            }

            servo_rand_pulse_width = random_int_range(1200, 1800);
            McpwmServo_setPulseWidth(&servo[0], servo_rand_pulse_width);

            counter++;
            if(counter > counter_target)
            {
                counter_target = 0;
                counter = 0;
                isServoTrigger = 0;
            }      
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

static void step_logic_task(void *pvParameters)
{
    vTaskDelay(pdMS_TO_TICKS(1500));
    uint8_t rand_mode = 0;
    uint8_t tease_cat_counter = 0;
    
    while (1)
    {
        if(isTeaseCatAuto)
        {
            step_task_trigger_tease_cat();
        }

        if(isFindCatEnable)
        {
            step_trigger_servo_random_move();
            step_task_trigger_stop();
            vTaskDelay(pdMS_TO_TICKS(500));
        }
        else if(isTeaseCatEnable)
        {
            rand_mode = random_int_range(0, 1);
            if(rand_mode)
            {
                step_trigger_yaw_random_move();
            }
            else
            {
                step_trigger_servo_random_move();
            }

            tease_cat_counter++;
            if(tease_cat_counter > 3)
            {
                tease_cat_counter = 0;
                step_task_trigger_stop();
            }
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
        else
        {
            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }
    
}
