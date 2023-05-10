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

#define SERVO_PULSE_GPIO      (32)

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
static uint8_t YawMode = 1;

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
  xTaskCreate(step_x_task, "step_x_task", 4096, NULL, 5, NULL);
  xTaskCreate(servo_task, "servo_task", 4096, NULL, 5, NULL);
  xTaskCreate(step_logic_task, "step_logic_task", 4096, NULL, 5, NULL);
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


static void YawSymmetryMode(uint16_t speed, uint16_t step, uint8_t cnt)
{
    StepperYaw.setSpeed(speed, 200, 200);

    stepSetPosWait(StepperYaw, step);
    for(int i = 0; i < cnt; i++)
    {
        stepSetPosWait(StepperYaw, -step*2);
        stepSetPosWait(StepperYaw, step*2);
    }
    stepSetPosWait(StepperYaw, -step);
}

static void XSymmetryMode(uint16_t speed, uint16_t step, uint8_t cnt)
{
    StepperX.setSpeed(speed, 1000, 1000);

    stepSetPosWait(StepperX, step);
    for(int i = 0; i < cnt; i++)
    {
        stepSetPosWait(StepperX, -step*2);
        stepSetPosWait(StepperX, step*2);
    }
    stepSetPosWait(StepperX, -step);
}

static void mode_0(uint8_t cnt)
{
    YawSymmetryMode(2000, 1000, cnt);
}

static void mode_1(uint8_t cnt)
{
    YawSymmetryMode(50000, 400, cnt);
}

static void step_yaw_task(void *pvParameters)
{
    DendoStepper_config_t step_cfg = {
        .stepPin = STEPPER1_PIN_STP,
        .dirPin = STEPPER1_PIN_DIR,
        .enPin = STEPPER1_PIN_EN,
        .timer_group = TIMER_GROUP_0,
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
                case 1:
                {
                    mode_1(5);
                }
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

static void step_x_task(void *pvParameters)
{
    int ret = 0;
    DendoStepper_config_t step_cfg = {
        .stepPin = STEPPER2_PIN_STP,
        .dirPin = STEPPER2_PIN_DIR,
        .enPin = STEPPER2_PIN_EN,
        .timer_group = TIMER_GROUP_0,
        .timer_idx = TIMER_1,
        .miStep = MICROSTEP_16,
        .stepAngle = 1.8
    };

    StepperX.config(&step_cfg);
    StepperX.init();

    /* limiter init */
    for(int i = 0; i < SLIDERAIL_LIMITER_IDX_MAX; i++)
    {
        ret = Limiter_init(&limiter[i]);
        ESP_ERROR_CHECK_WITHOUT_ABORT(ret);
    }

    vTaskDelay(pdMS_TO_TICKS(1000));

    // step_trigger_random_move();

    while (isRunning)
    {
        XSymmetryMode(10000, 22000, 2);
        // if(isXTrigger)
        // {
        //     switch(YawMode)
        //     {
        //         case 0:
        //         {
        //             mode_0(5);
        //         }
        //         break;
        //         case 1:
        //         {
        //             mode_1(5);
        //         }
        //         break;

        //     }
        //     isXTrigger = 0;
        // }
        // else
        // {
        //     vTaskDelay(pdMS_TO_TICKS(10));
        // }

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

            servo_rand_pulse_width = random_int_range(1000, 2000);
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
    
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(2000));
        rand_mode = random_int_range(0, 1);
        if(rand_mode)
        {
            step_trigger_yaw_random_move();
        }
        else
        {
            step_trigger_servo_random_move();
        }
    }
    
}
