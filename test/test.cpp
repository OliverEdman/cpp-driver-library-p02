#include <cstdio>

#include "driver/adc/stub.h"

int main()
{
    driver::adc::Stub adc{};
    adc.init();
    adc.simulateInput(230U);
    std::printf("ADC input: %u!\n", adc.readRaw());
}