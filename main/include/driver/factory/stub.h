#pragma once

#include "interface.h"
#include <memory>
#include <cstdint>

#include "driver/adc/stub.h"
#include "driver/serial/stub.h"
#include "driver/timer/stub.h"
#include "driver/tempsensor/stub.h"

namespace driver::factory {

class Stub final : public Interface {
public:

    Stub() noexcept = default;
    ~Stub() noexcept override = default;

    /** @return nullptr since the GPIO driver is not implemented yet. */
    std::unique_ptr<gpio::Interface> gpioInput(std::uint8_t pin) noexcept override {
        (void)pin;
        return nullptr; 
    }

    /** @return nullptr since the GPIO driver is not implemented yet. */
    std::unique_ptr<gpio::Interface> gpioOutput(std::uint8_t pin) noexcept override {
        (void)pin;
        return nullptr; 
    }

    /** @return A smart pointer to the created ADC interface. */
    std::unique_ptr<adc::Interface> adc(std::uint8_t pin) noexcept override {
        (void)pin;
        return std::make_unique<driver::adc::Stub>();
    }

    /** @return A smart pointer to the created Serial interface. */
    std::unique_ptr<serial::Interface> serial(std::uint32_t baud_bps) noexcept override {
        (void)baud_bps;
        return std::make_unique<driver::serial::Stub>();
    }

    /** @return A smart pointer to the created Temperature sensor interface. */
    std::unique_ptr<tempsensor::Interface> tempSensor(std::uint8_t pin, adc::Interface& adc) noexcept override {
        (void)pin;
        (void)adc;
        return std::make_unique<driver::tempsensor::Stub>();
    }

    /** @return A smart pointer to the created Timer interface. */
    std::unique_ptr<timer::Interface> timer(std::uint16_t timeout_ms) noexcept override {
        (void)timeout_ms;
        return std::make_unique<driver::timer::Stub>(); 
    }

    // No copy and move
    Stub(const Stub&)            = delete;
    Stub& operator=(const Stub&) = delete;
    Stub(Stub&&)                 = delete;
    Stub& operator=(Stub&&)      = delete;
};

} // namespace driver::factory
