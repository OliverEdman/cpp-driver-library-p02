#include <cstdio>

#include "driver/adc/stub.h"
#include "system/pin_manager/esp32s3.h"

int main()
{
    system::pin_manager::Esp32s3::instance().isPinBusy(5ULL);
    driver::adc::Stub adc{};
    adc.simulateInput(100U);
    std::printf("ADC input: %u!\n", adc.read());
}