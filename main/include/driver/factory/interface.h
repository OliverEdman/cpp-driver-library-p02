#pragma once

#include <cstdint>
#include <memory>

namespace driver {
    namespace adc { class Interface; }
    namespace gpio { class Interface; }
    namespace serial { class Interface; }
    namespace tempsensor { class Interface; }
    namespace timer { class Interface; }
} 

namespace driver::factory {

/**
 * @brief Abstract Factory interface for creating drivers.
 */
class Interface {
protected:

    /**
     * @brief Protected constructor to allow inheritance but prevent creating objects directly.
     */

    Interface() noexcept = default;

public:
    virtual ~Interface() noexcept = default;

    /** @return A smart pointer to the created ADC interface. */
    virtual std::unique_ptr<adc::Interface> adc(std::uint8_t pin) noexcept = 0;

    /** @return A smart pointer to the created GPIO input instance. */
    virtual std::unique_ptr<gpio::Interface> gpioInput(std::uint8_t pin) noexcept = 0;

    /** @return A smart pointer to the created GPIO output instance. */
    virtual std::unique_ptr<gpio::Interface> gpioOutput(std::uint8_t pin) noexcept = 0;

    /** @return A smart pointer to the created Serial instance. */
    virtual std::unique_ptr<serial::Interface> serial(std::uint32_t baud_bps) noexcept = 0;

    /** @return A smart pointer to the created Temperature sensor instance (Dependency Injection). */
    virtual std::unique_ptr<tempsensor::Interface> tempSensor(std::uint8_t pin, adc::Interface& adc) noexcept = 0;

    /** @return A smart pointer to the created Timer instance. */
    virtual std::unique_ptr<timer::Interface> timer(std::uint16_t timeout_ms) noexcept = 0;

    // No copy and move operations allowed
    Interface(const Interface&)            = delete;
    Interface& operator=(const Interface&) = delete;
    Interface(Interface&&)                 = delete;
    Interface& operator=(Interface&&)      = delete;
};

} // namespace driver::factory
