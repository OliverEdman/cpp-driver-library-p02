#include <cstdio>

#include "driver/gpio/stub.h"

int main()
{
    driver::gpio::Stub gpio{};
    gpio.write(false);
    std::printf("gpio funkar %u!\n",gpio.read());
}