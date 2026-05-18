#pragma once

#include "interface.h"
#include <memory>
#include <cstdint>

#include "driver/adc/stub.h"
#include "driver/serial/stub.h"
#include "driver/timer/stub.h"
#include "driver/tempsensor/stub.h"


namespace driver::gpio {
    enum class Direction : std::uint8_t;
    class Interface;
}

namespace driver::factory {

class Stub final : public Interface {
public:

    Stub() noexcept = default;
    ~Stub() noexcept override = default;

    /**
     * @brief Create a GPIO driver instance.
     * @param[in] pin The GPIO pin number.
     * @param[in] direction The pin direction (Input/Output).
     * @return nullptr since the GPIO driver is not implemented yet.
     */

    std::unique_ptr<gpio::Interface> gpio(std::uint8_t pin, gpio::Direction direction) noexcept override {
        (void)pin;
        (void)direction;
        return nullptr; 
    }

    /**
     * @brief Create an ADC driver instance.
     * @return A smart pointer to the created ADC interface.
     */

    std::unique_ptr<adc::Interface> adc() noexcept override {
        return std::make_unique<driver::adc::Stub>();
    }

    /**
     * @brief Create a Serial (UART) driver instance.
     * @return A smart pointer to the created Serial interface.
     */

    std::unique_ptr<serial::Interface> serial() noexcept override {
        return std::make_unique<driver::serial::Stub>();
    }

    /** * @brief Create a Timer driver instance.
     * @return A smart pointer to the created Timer interface.
     */

    std::unique_ptr<timer::Interface> timer() noexcept override {
        return std::make_unique<driver::timer::Stub>(); 
    }

    /**
     * @brief Create a Temperature driver instance.
     * @param[in] pin the Pin number where the TMP36 sensor is connected.
     * @param[in] adc A reference to the adc instance used for reading voltage (Dependency Injection).
     * @return A smart pointer to the created Temperature sensor interface.
     */

    std::unique_ptr<tempsensor::Interface> tempsensor(std::uint8_t pin, adc::Interface& adc) noexcept override {
        (void)pin;
        return std::make_unique<driver::tempsensor::Stub>(adc);
    }

    // No copy and move
    Stub(const Stub&)            = delete;
    Stub& operator=(const Stub&) = delete;
    Stub(Stub&&)                 = delete;
    Stub& operator=(Stub&&)      = delete;
};
} // namespace driver::factory
