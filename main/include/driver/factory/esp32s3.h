/**
 * @file esp32s3.h
 * @brief Interface for the ESP32-S3 driver
 */

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
    namespace mqtt { class Interface; }
    namespace wifi { class Interface; }
} 

namespace driver::factory {

/**
 * @brief Factory for creating real ESP32-S3 hardware drivers.
 */

class Esp32s3 final : public Interface {
public:
    Esp32s3() noexcept = default;
    ~Esp32s3() noexcept override = default;

    /**
     * @brief Create a real ESP32-S3 ADC hardware instance.
     * * @param[in] pin The hardware pin number to use for the ADC channel.
     * @return A unique pointer to the created ADC interface instance.
     */
    std::unique_ptr<adc::Interface> adc(std::uint8_t pin) noexcept override;

    /**
     * @brief Create a real ESP32-S3 GPIO input hardware instance.
     * * @param[in] pin The hardware pin number to configure as input.
     * @return A unique pointer to the created GPIO interface instance.
     */
    std::unique_ptr<gpio::Interface> gpioInput(std::uint8_t pin) noexcept override;

    /**
     * @brief Create a real ESP32-S3 GPIO output hardware instance.
     * * @param[in] pin The hardware pin number to configure as output.
     * @return A unique pointer to the created GPIO interface instance.
     */
    std::unique_ptr<gpio::Interface> gpioOutput(std::uint8_t pin) noexcept override;

    /**
     * @brief Create a real ESP32-S3 Serial UART hardware instance.
     * * @param[in] baud_bps The communication speed in bits per second (baud rate).
     * @return A unique pointer to the created Serial interface instance.
     */
    std::unique_ptr<serial::Interface> serial(std::uint32_t baud_bps) noexcept override;

    /**
     * @brief Create a real TMP36 Temperature sensor hardware instance.
     * * @param[in] pin The hardware pin number connected to the temperature sensor.
     * @param[in] adc Reference to the initialized ADC driver instance to use for reading.
     * @return A unique pointer to the created Temperature Sensor interface instance.
     */
    std::unique_ptr<tempsensor::Interface> tempSensor(std::uint8_t pin, adc::Interface& adc) noexcept override;

    /**
     * @brief Create a real ESP32-S3 Timer hardware instance.
     * * @param[in] timeout_ms The timer timeout duration specified in milliseconds.
     * @return A unique pointer to the created Timer interface instance.
     */
    std::unique_ptr<timer::Interface> timer(std::uint32_t timeout_ms) noexcept override;

    /**
     * @brief Create a real ESP32-S3 WiFi hardware instance.
     *
     * @param[in] ssid WiFi network SSID.
     * @param[in] password WiFi network password.
     * @return A unique pointer to the created WiFi interface instance.
     */
    std::unique_ptr<wifi::Interface> wifi(const char* ssid, const char* password) noexcept override;

    /**
     * @brief Create a real ESP32-S3 MQTT hardware instance.
     *
     * @param[in]  brokerUri MQTT broker URI.
     * @param[in] clientId  MQTT client ID.
     * @return A unique pointer to the created MQTT interface instance.
     */
    std::unique_ptr<mqtt::Interface> mqtt(const char* brokerUri, const char* clientId) noexcept override;

    // no copy move operators
    Esp32s3(const Esp32s3&)            = delete;
    Esp32s3& operator=(const Esp32s3&) = delete;
    Esp32s3(Esp32s3&&)                 = delete;
    Esp32s3& operator=(Esp32s3&&)      = delete;
};

} // namespace driver::factory
