/**
 * @file interface.h
 * @brief Abstract interface for creating driver instances.
 */

#pragma once

#include <cstdint>
#include <memory>

namespace driver::adc { class Interface; }
namespace driver::gpio { class Interface; }
namespace driver::serial { class Interface; }
namespace driver::tempsensor { class Interface; }
namespace driver::timer { class Interface; }

namespace driver::factory {

/**
 * @brief Abstract Factory interface for creating drivers.
 */
class Interface {


public:
    virtual ~Interface() noexcept = default;

    /**
     * @brief Create an ADC driver instance.
     *
     * @param[in] pin The hardware pin number to use for the ADC channel.
     * @return A unique pointer to the created ADC interface instance.
     */
    virtual std::unique_ptr<adc::Interface> adc(std::uint8_t pin) noexcept = 0;

    /**
     * @brief Create a GPIO input driver instance.
     *
     * @param[in] pin The hardware pin number to configure as input.
     * @return A unique pointer to the created GPIO interface instance.
     */
    virtual std::unique_ptr<gpio::Interface> gpioInput(std::uint8_t pin) noexcept = 0;

    /**
     * @brief Create a GPIO output driver instance.
     *
     * @param[in] pin The hardware pin number to configure as output.
     * @return A unique pointer to the created GPIO interface instance.
     */
    virtual std::unique_ptr<gpio::Interface> gpioOutput(std::uint8_t pin) noexcept = 0;

    /**
     * @brief Create a Serial UART driver instance.
     *
     * @param[in] baud_bps The communication speed in bits per second (baud rate).
     * @return A unique pointer to the created Serial interface instance.
     */
    virtual std::unique_ptr<serial::Interface> serial(std::uint32_t baud_bps) noexcept = 0;

    /**
     * @brief Create a Temperature sensor driver instance using Dependency Injection.
     *
     * @param[in] pin The hardware pin number connected to the temperature sensor.
     * @param[in] adc Reference to an initialized ADC driver instance used for reading.
     * @return A unique pointer to the created Temperature Sensor interface instance.
     */
    virtual std::unique_ptr<tempsensor::Interface> tempSensor(std::uint8_t pin, adc::Interface& adc) noexcept = 0;

    /**
     * @brief Create a Timer driver instance.
     *
     * @param[in] timeout_ms The timer timeout duration specified in milliseconds.
     * @return A unique pointer to the created Timer interface instance.
     */
    virtual std::unique_ptr<timer::Interface> timer(std::uint32_t timeout_ms) noexcept = 0;

    // No copy and move operations allowed
    Interface(const Interface&)            = delete;
    Interface& operator=(const Interface&) = delete;
    Interface(Interface&&)                 = delete;
    Interface& operator=(Interface&&)      = delete;


protected:

    /**
     * @brief Protected constructor to allow inheritance but prevent creating objects directly.
     */

    Interface() noexcept = default;
};

} // namespace driver::factory
