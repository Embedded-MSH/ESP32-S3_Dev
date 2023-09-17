#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_ctrl.h"
#include "sdkconfig.h"

#include <stdio.h>

static const char* TAG = "Main";

void app_main(void)
{

    ESP_LOGI(TAG, "My ESP32-S3 Ctrl Test!");
    /* Configure the peripheral according to the LED type */
    init_led();

    while (1) {
        blink_led();
        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    }
}
