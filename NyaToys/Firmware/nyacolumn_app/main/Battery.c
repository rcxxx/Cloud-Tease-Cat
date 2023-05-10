/**
 ******************************************************************************
 * @file           Battery.c
 * @description:   
 * @author:        Hare
 * @date:          2023-01-23
 * @version:       v0.1
 * @history: 
 *    [version]   [date]       [author]       [description]
 *    v0.1   	    2023-01-23   Hare           create
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "Battery.h"
#include "Filter.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

/* Defines -------------------------------------------------------------------*/
#define TAG       "BatteryMonitor"

#define BAT_ADC1_CHAN               ADC1_CHANNEL_6
//ADC Attenuation
#define ADC_EXAMPLE_ATTEN           ADC_ATTEN_DB_11
//ADC Calibration
#define ADC_EXAMPLE_CALI_SCHEME     ESP_ADC_CAL_VAL_EFUSE_VREF

#define CHARGE_DET_PIN            (33)
#define BAT_AD_PIN                (34)

#define BAT_AD_FILTER_FACTOR      (0.4f)

#define BAT_AD_RES_VAL_R1         (100.0f)
#define BAT_AD_RES_VAL_R2         (30.0f)

#define BAT_VOLT_MAX              (3 * 4.2f)
#define BAT_VOLT_MIN              (3 * 3.7f)

/* Private types -------------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static esp_adc_cal_characteristics_t adc1_chars;
static uint8_t adc_cali_enable = 0;

static int adc_raw;
static float adc_cal_mv;
static float adc_lpf_mv;

static Battery_Info_t Battery_Info;


/* Private macro -------------------------------------------------------------*/
#define GET_SOURCEVOLT(in, r1, r2)    (in / (r2 / (r1 + r2)))

/* Import function prototypes ------------------------------------------------*//* Private function prototypes -----------------------------------------------*/
static int adc_init(void);
static void BatteryMonitor_task(void *arg);

/* Exported functions --------------------------------------------------------*/
int BatteryMonitor_init(void)
{
  adc_init();

  /* charge detect io init */
  gpio_config_t io_conf;
  io_conf.intr_type = GPIO_INTR_DISABLE;
  io_conf.pull_down_en = 0;
  io_conf.pull_up_en = 0;
  io_conf.mode = GPIO_MODE_INPUT;

  io_conf.pin_bit_mask = BIT64(CHARGE_DET_PIN);
  ESP_ERROR_CHECK(gpio_config(&io_conf));

  xTaskCreate(BatteryMonitor_task, "BatteryMonitor", 2048, NULL, 1, NULL);
  return 0;
}

Battery_Info_t* BatteryMonitor_getInfo(void)
{
  return &Battery_Info;
}

/* Private functions ---------------------------------------------------------*/
static bool adc_calibration(void)
{
    esp_err_t ret;
    bool cali_enable = false;

    ret = esp_adc_cal_check_efuse(ADC_EXAMPLE_CALI_SCHEME);
    if (ret == ESP_ERR_NOT_SUPPORTED) {
        ESP_LOGW(TAG, "Calibration scheme not supported, skip software calibration");
    } else if (ret == ESP_ERR_INVALID_VERSION) {
        ESP_LOGW(TAG, "eFuse not burnt, skip software calibration");
    } else if (ret == ESP_OK) {
        cali_enable = true;
        esp_adc_cal_characterize(ADC_UNIT_1, ADC_EXAMPLE_ATTEN, ADC_WIDTH_BIT_DEFAULT, 0, &adc1_chars);
        // esp_adc_cal_characterize(ADC_UNIT_2, ADC_EXAMPLE_ATTEN, ADC_WIDTH_BIT_DEFAULT, 0, &adc2_chars);
    } else {
        ESP_LOGE(TAG, "Invalid arg");
    }

    return cali_enable;
}

static int adc_init(void)
{
  adc_cali_enable = adc_calibration();
  ESP_LOGI(TAG, "adc_cali_enable=%d", adc_cali_enable);

  //ADC1 config
  ESP_ERROR_CHECK(adc1_config_width(ADC_WIDTH_BIT_DEFAULT));
  ESP_ERROR_CHECK(adc1_config_channel_atten(BAT_ADC1_CHAN, ADC_EXAMPLE_ATTEN));
  return 0;
}

static void BatteryMonitor_task(void *arg)
{
  uint8_t init_flag = 0;
  while(1)
  {
    adc_raw = adc1_get_raw(BAT_ADC1_CHAN);
    if (adc_cali_enable) {
      adc_cal_mv = esp_adc_cal_raw_to_voltage(adc_raw, &adc1_chars);
      ESP_LOGV(TAG, "cali data: %f mV", adc_cal_mv);
    }

    if(init_flag == 1)
    {
      Filter_IIRLPF(&adc_cal_mv, &adc_lpf_mv, BAT_AD_FILTER_FACTOR);
    }
    else
    {
      adc_lpf_mv = adc_cal_mv;
      Battery_Info.voltage = GET_SOURCEVOLT(adc_lpf_mv/1000, BAT_AD_RES_VAL_R1, BAT_AD_RES_VAL_R2);
      Battery_Info.voltageMinMax = Battery_Info.voltage;
      init_flag = 1;
    }

    Battery_Info.voltage = GET_SOURCEVOLT(adc_lpf_mv/1000, BAT_AD_RES_VAL_R1, BAT_AD_RES_VAL_R2);
    Battery_Info.isCharging = !gpio_get_level(CHARGE_DET_PIN);
    
    if(Battery_Info.isCharging)
    {
      if(Battery_Info.voltage > Battery_Info.voltageMinMax)
      {
        Battery_Info.voltageMinMax = Battery_Info.voltage;
      }
    }
    else
    {
      if(Battery_Info.voltage < Battery_Info.voltageMinMax)
      {
        Battery_Info.voltageMinMax = Battery_Info.voltage;
      }
    }

    float percent = (Battery_Info.voltageMinMax - BAT_VOLT_MIN)/(BAT_VOLT_MAX - BAT_VOLT_MIN)*100;
    if(Battery_Info.isCharging && percent > 99)
    {
      Battery_Info.percent = 99;
    }
    else if(percent > 100)
    {
      Battery_Info.percent = 100;
    }
    else if(percent < 0)
    {
      Battery_Info.percent = 0;
    }
    else
    {
      Battery_Info.percent = percent;
    }
    
    ESP_LOGV(TAG, "BAT %.1f V, (%.1f%%) charge=%d", Battery_Info.voltageMinMax, Battery_Info.percent, Battery_Info.isCharging);

    vTaskDelay(pdMS_TO_TICKS(200));
  }
}
