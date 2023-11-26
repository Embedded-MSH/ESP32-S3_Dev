#include "18b20_ctrl.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "lcd_ctrl.h"
#include "led_ctrl.h"
#include "misc/lv_timer.h"
#include "sdkconfig.h"
#include "wifi_ap_ctrl.h"

#include <stdio.h>

static TaskHandle_t lvgl_task_handle = NULL;
static TaskHandle_t get_temperature_handle = NULL;

static const char* TAG = "Main";

void getTempAddresses(DeviceAddress* tempSensorAddresses)
{
    unsigned int numberFound = 0;
    reset_search();
    // search for 2 addresses on the oneWire protocol
    while (search(tempSensorAddresses[numberFound], true)) {
        numberFound++;
        if (numberFound == 2)
            break;
    }
    ESP_LOGI(TAG, "Found %d temp sensors", numberFound);
    return;
}

void get_temperature_task()
{
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
        blink_led();
        // ds18b20_requestTemperatures();
        // float temp1 = ds18b20_getTempF((DeviceAddress*)tempSensors[0]);
        // float temp3 = ds18b20_getTempC((DeviceAddress*)tempSensors[0]);
        // printf("Temperatures: %0.1fF \n", temp1);
        // printf("Temperatures: %0.1fC \n", temp3);

        float cTemp = ds18b20_get_temp();
        char buffer[40] = { 0 };
        snprintf(buffer, sizeof(buffer), "Temperature: %0.1fC\n", cTemp);
        ESP_LOGI(TAG, "%s", buffer);
        updateTemp(buffer);
    }
}

void lvgl_task()
{
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(10));
        lv_timer_handler();
    }
}
void app_main(void)
{
    ESP_LOGI(TAG, "My ESP32-S3 init!");

    ESP_LOGI(TAG, "Init Led Ctrl!");
    init_led();

    ESP_LOGI(TAG, "Init WIFI AP MODE!");
    init_ap_mode();

    ESP_LOGI(TAG, "Init LCD SPI Ctrl!");
    init_lcd();
    blink_led();
    DeviceAddress tempSensors[2];
    ds18b20_init(0);
    getTempAddresses(tempSensors);
    ESP_LOGI(
        TAG,
        "Address 0: 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x \n",
        tempSensors[0][0],
        tempSensors[0][1],
        tempSensors[0][2],
        tempSensors[0][3],
        tempSensors[0][4],
        tempSensors[0][5],
        tempSensors[0][6],
        tempSensors[0][7]);
    // ds18b20_setResolution(tempSensors, 1, 10);

    // Allow other core to finish initialization
    vTaskDelay(pdMS_TO_TICKS(100));

    // Create semaphores to synchronize
    xTaskCreatePinnedToCore(lvgl_task,
                            "lvgl_task",
                            1024 * 4,
                            NULL,
                            1,
                            &lvgl_task_handle,
                            0);
    xTaskCreatePinnedToCore(get_temperature_task,
                            "get_temperature_task",
                            1024 * 4,
                            NULL,
                            1,
                            &get_temperature_handle,
                            0);
    while (1) {

        vTaskDelay(pdMS_TO_TICKS(1000));
        // vTaskDelay(pdMS_TO_TICKS(10));
        // count += 1;
        // if (count > 100) {
        //     count = 0;
        //     blink_led();
        //     // ds18b20_requestTemperatures();
        //     // float temp1 =
        //     ds18b20_getTempF((DeviceAddress*)tempSensors[0]);
        //     // float temp3 =
        //     ds18b20_getTempC((DeviceAddress*)tempSensors[0]);
        //     // printf("Temperatures: %0.1fF \n", temp1);
        //     // printf("Temperatures: %0.1fC \n", temp3);

        //     float cTemp = ds18b20_get_temp();
        //     char buffer[40] = { 0 };
        //     snprintf(buffer, sizeof(buffer), "Temperature: %0.1fC\n", cTemp);
        //     ESP_LOGI(TAG, "%s", buffer);
        //     updateTemp(buffer);
        // }
        // lv_timer_handler();
    }
}
