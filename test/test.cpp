#include <cstdio>

#include "driver/adc/stub.h"

int main()
{
    driver::adc::Stub adc{};
    adc.simulateInput(100U);
    std::printf("ADC input: %u!\n", adc.read());
}