#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
// #include "lcd_ctrl.h"
// #include "led_ctrl.h"
// #include "misc/lv_timer.h"
#include "sdkconfig.h"
#include "wifi_ap_ctrl.h"

#include <stdio.h>

static const char* TAG = "Main";

void app_main(void)
{
    ESP_LOGI(TAG, "My ESP32-S3 init!");

    ESP_LOGI(TAG, "Init Led Ctrl!");
    // init_led();

    ESP_LOGI(TAG, "Init WIFI AP MODE!");
    init_ap_mode();

    ESP_LOGI(TAG, "Init LCD SPI Ctrl!");
    // init_lcd();
    size_t count = 0;
    // blink_led();
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(10));
        count += 1;
        if (count > 100) {
            count = 0;
            // blink_led();
        }
        // lv_timer_handler();
    }
}
