#include "driver/timer/esp32s3.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern "C" void app_main(void)
{
    // test kod bara för att ha något i main innan vi har gjort factory och logic
    driver::timer::Esp32s3 testTimer;
    testTimer.setPeriod(1000);
    testTimer.start();

    while (true)
    {
        if (testTimer.isTimeout())
        {
            ESP_LOGI("TEST", "Timer is working!");
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
