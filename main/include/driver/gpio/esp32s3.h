/**
 * @brief GPIO driver for ESP32-S3.
 */
#pragma once

#include <cstdint>

#include "driver/gpio/direction.h"
#include "driver/gpio/interface.h"

namespace driver::gpio
{
/**
 * @brief GPIO driver Esp32-S3.
 * 
 *        This class is non-copyable and non-movable.
 */
class Esp32s3 final : public Interface
{
public:
    /**
     * @brief Constructor.
     * 
     * @param[in] pin GPIO pin. Must be supported by ESP32-S3.
     * @param[in] direction Data direction.
     */
    explicit Esp32s3(std::uint8_t pin, Direction direction) noexcept;

    /**
     * @brief Destructor.
     */
    ~Esp32s3() noexcept override;

    /**
     * @brief Write GPIO state.
     * 
     * @param[in] state True to enable the GPIO, false otherwise.
     */
    void write(bool state) noexcept override;

    /**
     * @brief Read GPIO state.
     * 
     * @return True if the GPIO is active/high, false otherwise.
     */
    bool read() const noexcept override;

    /**
     * @brief Toggle the GPIO.
     */
    void toggle() noexcept override;

    Esp32s3()                          = delete; // No default constructor (we need a pin).
    Esp32s3(const Esp32s3&)            = delete; // No copy constructor.
    Esp32s3(Esp32s3&&)                 = delete; // No move constructor.
    Esp32s3& operator=(const Esp32s3&) = delete; // No copy assignment.
    Esp32s3& operator=(Esp32s3&&)      = delete; // No move assignment.

private:
    /** GPIO pin. */
    const std::uint8_t myPin;
};
} // namespace driver::gpio
