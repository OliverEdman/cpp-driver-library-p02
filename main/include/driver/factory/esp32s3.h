#pragma once

#include "interface.h"
#include <memory>
#include <cstdint>


namespace driver {
    namespace adc { class Interface; }
    namespace gpio { class Interface; }
    namespace serial { class Interface; }
    namespace tempsensor { class Interface; }
    namespace timer { class Interface; }
} 

namespace driver::factory {

/**
 * @brief Factory for creating real ESP32-S3 hardware drivers.
 */

class Esp32s3 final : public Interface {
public:
    Esp32s3() noexcept = default;
    ~Esp32s3() noexcept override = default;

    /** @return A smart pointer to the real ESP32-S3 ADC instance. */
    std::unique_ptr<adc::Interface> adc(std::uint8_t pin) noexcept override;

    /** @return A smart pointer to the real ESP32-S3 GPIO input instance. */
    std::unique_ptr<gpio::Interface> gpioInput(std::uint8_t pin) noexcept override;

    /** @return A smart pointer to the real ESP32-S3 GPIO output instance. */
    std::unique_ptr<gpio::Interface> gpioOutput(std::uint8_t pin) noexcept override;

    /** @return A smart pointer to the real ESP32-S3 Serial instance. */
    std::unique_ptr<serial::Interface> serial(std::uint32_t baud_bps) noexcept override;

    /** @return A smart pointer to the real TMP36 Temperature sensor instance. */
    std::unique_ptr<tempsensor::Interface> tempSensor(std::uint8_t pin, adc::Interface& adc) noexcept override;

    /** @return A smart pointer to the real ESP32-S3 Timer instance. */
    std::unique_ptr<timer::Interface> timer(std::uint32_t timeout_ms) noexcept override;

    // no copy move operators
    Esp32s3(const Esp32s3&)            = delete;
    Esp32s3& operator=(const Esp32s3&) = delete;
    Esp32s3(Esp32s3&&)                 = delete;
    Esp32s3& operator=(Esp32s3&&)      = delete;
};

} // namespace driver::factory
