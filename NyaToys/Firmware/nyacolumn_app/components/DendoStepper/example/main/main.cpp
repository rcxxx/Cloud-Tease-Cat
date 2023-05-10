#include <stdio.h>
#include "DendoStepper.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

DendoStepper step;
DendoStepper step1;

extern "C" void app_main(void)
{
    DendoStepper_config_t step_cfg = {
        .stepPin = 16,
        .dirPin = 17,
        .enPin = 15,
        .timer_group = TIMER_GROUP_0,
        .timer_idx = TIMER_0,
        .miStep = MICROSTEP_32,
        .stepAngle = 1.8};

    DendoStepper_config_t step1_cfg = {
        .stepPin = 18,
        .dirPin = 19,
        .enPin = 20,
        .timer_group = TIMER_GROUP_0,
        .timer_idx = TIMER_1,
        .miStep = MICROSTEP_32,
        .stepAngle = 1.8};

    step.config(&step_cfg);
    step1.config(&step1_cfg);

    step.init();
    step1.init();

    step.setSpeed(10000, 1000, 1000);
    step1.setSpeed(20000, 1000, 1000);

    // step.runInf(true);
    step.setStepsPerMm(10);

    while (1)
    {
        step.runPosMm(500);
        step1.runPos(10000);
        vTaskDelay(1000);
        // step.runAbs(5000);
    }
}