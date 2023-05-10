/**
 ******************************************************************************
 * @file           gui_task.c
 * @description:
 * @author:        Hare
 * @date:          2023-01-19
 * @version:       v0.1
 * @history:
 *    [version]   [date]       [author]       [description]
 *    v0.1   	    2023-01-19   Hare           create
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "gui_task.h"
#include "StatusBar.h"
#include "MainPage.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "SysLog.h"
/* Littlevgl specific */
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
#include "lvgl_helpers.h"
// #include "lv_examples/src/lv_demo_stress/lv_demo_stress.h"
// #include "lv_examples/src/lv_demo_benchmark/lv_demo_benchmark.h"

/* Defines -------------------------------------------------------------------*/
#define TAG "GuiTask"
#define LV_TICK_PERIOD_MS 1

/* Private types -------------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static BaseType_t taskHandle;
static uint8_t isTerminal = 0;

/* Creates a semaphore to handle concurrent call to lvgl stuff
 * If you wish to call *any* lvgl function from other threads/tasks
 * you should lock on the very same semaphore! */
SemaphoreHandle_t xGuiSemaphore;

/* Private macro -------------------------------------------------------------*/

/* Import function prototypes ------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void guiTask(void *pvParameter);

/* Exported functions --------------------------------------------------------*/
int GuiTask_create()
{
  /* If you want to use a task to create the graphic, you NEED to create a Pinned task
     * Otherwise there can be problem such as memory corruption and so on.
     * NOTE: When not using Wi-Fi nor Bluetooth you can pin the guiTask to core 0 */
  taskHandle = xTaskCreatePinnedToCore(guiTask, "GuiTask", 4096*2, NULL, 0, NULL, 1);
  if (!taskHandle)
  {
    SYS_LOGE(TAG, "%s err, ret %d", __func__, taskHandle);
  }
  return 0;
}

int GuiTask_destroy()
{
  // int *ret = NULL;
  isTerminal = 1;
  // PTF_taskJoin(taskHandle, &ret);
  return 0;
}

/* Private functions ---------------------------------------------------------*/
static void lv_tick_task(void *arg)
{
  (void)arg;

  lv_tick_inc(LV_TICK_PERIOD_MS);
}

static void guiTask(void *pvParameter)
{
  (void)pvParameter;
  xGuiSemaphore = xSemaphoreCreateMutex();

  lv_init();

  /* Initialize SPI or I2C bus used by the drivers */
  lvgl_driver_init();

  lv_color_t *buf1 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA);
  assert(buf1 != NULL);

  /* Use double buffered when not working with monochrome displays */
#ifndef CONFIG_LV_TFT_DISPLAY_MONOCHROME
  lv_color_t *buf2 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA);
  assert(buf2 != NULL);
#else
  static lv_color_t *buf2 = NULL;
#endif

  static lv_disp_buf_t disp_buf;

  uint32_t size_in_px = DISP_BUF_SIZE;

#if defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_IL3820 || defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_JD79653A || defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_UC8151D || defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_SSD1306

  /* Actual size in pixels, not bytes. */
  size_in_px *= 8;
#endif

  /* Initialize the working buffer depending on the selected display.
   * NOTE: buf2 == NULL when using monochrome displays. */
  lv_disp_buf_init(&disp_buf, buf1, buf2, size_in_px);

  lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.flush_cb = disp_driver_flush;

#if defined CONFIG_DISPLAY_ORIENTATION_PORTRAIT || defined CONFIG_DISPLAY_ORIENTATION_PORTRAIT_INVERTED
  disp_drv.rotated = 1;
#endif

  /* When using a monochrome display we need to register the callbacks:
   * - rounder_cb
   * - set_px_cb */
#ifdef CONFIG_LV_TFT_DISPLAY_MONOCHROME
  disp_drv.rounder_cb = disp_driver_rounder;
  disp_drv.set_px_cb = disp_driver_set_px;
#endif

  disp_drv.buffer = &disp_buf;
  lv_disp_drv_register(&disp_drv);

  /* Register an input device when enabled on the menuconfig */
#if CONFIG_LV_TOUCH_CONTROLLER != TOUCH_CONTROLLER_NONE
  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.read_cb = touch_driver_read;
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  lv_indev_drv_register(&indev_drv);
#endif

  /* Create and start a periodic timer interrupt to call lv_tick_inc */
  const esp_timer_create_args_t periodic_timer_args = {
      .callback = &lv_tick_task,
      .name = "periodic_gui"};
  esp_timer_handle_t periodic_timer;
  ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
  ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));

  /* Create the demo application */
  // lv_demo_stress();
  // lv_demo_benchmark();
  StatusBar_create(lv_layer_top());
  MainPage_create(lv_scr_act());
  
  while (1)
  {
    StatusBar_update();
    MainPage_update();

    /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
    vTaskDelay(pdMS_TO_TICKS(10));

    /* Try to take the semaphore, call lvgl related function on success */
    if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
    {
      lv_task_handler();
      xSemaphoreGive(xGuiSemaphore);
    }
  }

  /* A task should NEVER return */
  free(buf1);
#ifndef CONFIG_LV_TFT_DISPLAY_MONOCHROME
  free(buf2);
#endif
  vTaskDelete(NULL);
}
