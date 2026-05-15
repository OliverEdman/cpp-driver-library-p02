#include <memory>
#include "driver/timer/esp32s3.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
extern "C" void app_main() {
    
    
    auto timer = std::make_unique<driver::timer::Esp32s3>();

    if (timer->isInitialized()) {
        timer->setPeriod(1000);
        timer->start();
        
        // TEST
        while (true) {
            if (timer->isTimeout()) {
                printf("Timeout triggered!\n");
            }
        
            vTaskDelay(pdMS_TO_TICKS(10)); 
        }
    }
}
