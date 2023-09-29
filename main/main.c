#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lcd_ctrl.h"
#include "led_ctrl.h"
#include "misc/lv_timer.h"
#include "sdkconfig.h"

#include <stdio.h>

static const char* TAG = "Main";

void app_main(void)
{
    ESP_LOGI(TAG, "My ESP32-S3 Ctrl Test!");
    /* Configure the peripheral according to the LED type */
    init_led();

    init_lcd();
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(10));
        // blink_led();
        lv_timer_handler();
    }
}
