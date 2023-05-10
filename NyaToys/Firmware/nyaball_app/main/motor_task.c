/**
 ******************************************************************************
 * @file           motor_task.c
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
#include "motor_task.h"
#include "mx113h_motor.h"
#include <string.h>
#include "util.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "SysLog.h"

/* Defines -------------------------------------------------------------------*/
#define MOTOR_IN1_PIN           (3)
#define MOTOR_IN2_PIN           (4)
#define MOTOR_TIMER             LEDC_TIMER_0
#define MOTOR_SPEED_MODE        LEDC_LOW_SPEED_MODE
#define MOTOR_PWM_FREQ_HZ       (15000)
#define MOTOR_IN1_CHANNEL       LEDC_CHANNEL_0
#define MOTOR_IN2_CHANNEL       LEDC_CHANNEL_1

/* Private types -------------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static Mx113hMoter_t motor = {
  .pwm_cfg = {
    .timer_cfg = {
        .speed_mode       = MOTOR_SPEED_MODE,
        .timer_num        = MOTOR_TIMER,
        .duty_resolution  = LEDC_TIMER_12_BIT,
        .freq_hz          = MOTOR_PWM_FREQ_HZ,
        .clk_cfg          = LEDC_AUTO_CLK
    },
    .ch1_cfg = {
        .speed_mode       = MOTOR_SPEED_MODE,
        .channel          = MOTOR_IN1_CHANNEL,
        .timer_sel        = MOTOR_TIMER,
        .intr_type        = LEDC_INTR_DISABLE,
        .gpio_num         = MOTOR_IN1_PIN,
        .duty             = 0, // Set duty to 0%
        .hpoint           = 0
    },
    .ch2_cfg = {
        .speed_mode       = MOTOR_SPEED_MODE,
        .channel          = MOTOR_IN2_CHANNEL,
        .timer_sel        = MOTOR_TIMER,
        .intr_type        = LEDC_INTR_DISABLE,
        .gpio_num         = MOTOR_IN2_PIN,
        .duty             = 0, // Set duty to 0%
        .hpoint           = 0
    },
  },
  .dir = 0,
};

static uint8_t trigger_flag = 0;

/* Private macro -------------------------------------------------------------*/

/* Import function prototypes ------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void motor_task(void *pvParameters);
static uint8_t isRunning = 0;

/* Exported functions --------------------------------------------------------*/
void motor_task_init(void)
{
  isRunning = 1;
  xTaskCreate(motor_task, "motor_task", 4096, NULL, 5, NULL);
}

void motor_task_exit(void)
{
  isRunning = 0;
}

void motor_task_trigger_random_move(void)
{
  if(!trigger_flag)
    trigger_flag = 1;
}

/* Private functions ---------------------------------------------------------*/
static void motor_task(void *pvParameters)
{
  Mx113hMotor_init(&motor);
  vTaskDelay(pdMS_TO_TICKS(2000));

  Mx113hMotor_setDuty(&motor, 50);
  vTaskDelay(pdMS_TO_TICKS(500));
  Mx113hMotor_setDuty(&motor, 0);

  while (isRunning)
  {
    if(trigger_flag)
    {
      uint16_t time = random_int_range(2000, 4000);
      uint16_t duty = random_int_range(40, 90);
      uint8_t dir = random_int_range(0, 1);
      uint16_t ramp_duty = 0;

      SYS_LOGI(__func__, "trig, time: %d, duty: %d, dir: %d", time, duty, dir);

      Mx113hMotor_setDuty(&motor, duty);

      while (ramp_duty < min(duty, 30))
      {
        ramp_duty += 2;
        Mx113hMotor_setDuty(&motor, ramp_duty);
        vTaskDelay(pdMS_TO_TICKS(100));
      }
      vTaskDelay(pdMS_TO_TICKS(time));
      Mx113hMotor_setDuty(&motor, 100);
      vTaskDelay(pdMS_TO_TICKS(500));
      Mx113hMotor_setDuty(&motor, 0);

      /* stop wait */
      vTaskDelay(pdMS_TO_TICKS(500));
      trigger_flag = 0;
    }
    vTaskDelay(pdMS_TO_TICKS(100));
  }

  Mx113hMotor_setDuty(&motor, 0);
  vTaskDelete(NULL);
}