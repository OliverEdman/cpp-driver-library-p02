/**
 * @file esp32s3.cpp
 * @brief Implementation of the ESP32-S3 hardware factory.
 */

#include "driver/factory/esp32s3.h"

#include "driver/adc/esp32s3.h"
#include "driver/gpio/esp32s3.h"
#include "driver/serial/esp32s3.h"
#include "driver/timer/esp32s3.h" 
#include "driver/tempsensor/tmp36.h"

namespace driver::factory {

/**
 * @brief Creates a real ESP32-S3 ADC driver instance.
 * @param[in] pin The hardware GPIO pin to associate with the ADC instance.
 * @return A unique pointer to the initialized ADC driver interface.
 */
std::unique_ptr<adc::Interface> Esp32s3::adc(std::uint8_t pin) noexcept {
    // Instante the real ADC driver and encapsulate the pin at construction
    return std::make_unique<driver::adc::Esp32s3>(pin);
}

/**
 * @brief Creates a real ESP32-S3 GPIO input driver instance.
 * @param[in] pin The hardware GPIO pin number.
 * @return A unique pointer to the initialized GPIO driver interface.
 */
std::unique_ptr<gpio::Interface> Esp32s3::gpioInput(std::uint8_t pin) noexcept {
    // Create a real GPIO pin configured as an input
    return std::make_unique<driver::gpio::Esp32s3>(pin, driver::gpio::Direction::Input);
}

/**
 * @brief Creates a real ESP32-S3 GPIO output driver instance.
 * @param[in] pin The hardware GPIO pin number.
 * @return A unique pointer to the initialized GPIO driver interface.
 */
std::unique_ptr<gpio::Interface> Esp32s3::gpioOutput(std::uint8_t pin) noexcept {
    // Create a real GPIO pin configured as an output
    return std::make_unique<driver::gpio::Esp32s3>(pin, driver::gpio::Direction::Output);
}

/**
 * @brief Creates a real ESP32-S3 Serial/UART driver instance.
 * @param[in] baud_bps The communication speed in bits per second.
 * @return A unique pointer to the initialized Serial driver interface.
 */
std::unique_ptr<serial::Interface> Esp32s3::serial(std::uint32_t baud_bps) noexcept {
    // Create the real UART driver with the specified baud rate
    const driver::serial::Config config{
        .port       = UART_NUM_0,       // unused in USB-JTAG mode
        .txPin      = UART_PIN_NO_CHANGE,
        .rxPin      = UART_PIN_NO_CHANGE,
        .baudRate   = static_cast<int>(baud_bps),
        .rxBufSize  = 256U,
        .useUsbJtag = true,
    };
    return std::make_unique<driver::serial::Esp32s3>(config);
}

/**
 * @brief Creates a real TMP36 temperature sensor instance.
 * @param[in] pin The hardware GPIO pin the sensor's Vout is connected to.
 * @param[in] adc Reference to the ADC driver instance used for voltage measurement.
 * @return A unique pointer to the initialized temperature sensor interface.
 */
std::unique_ptr<tempsensor::Interface> Esp32s3::tempSensor(std::uint8_t pin, adc::Interface& adc) noexcept {
    // Inject both the hardware pin and the required ADC dependency into the TMP36 instance
    return std::make_unique<driver::tempsensor::Tmp36>(adc, pin);
}

/**
 * @brief Creates a real ESP32-S3 hardware timer instance.
 * @param[in] timeout_ms The period/timeout duration in milliseconds.
 * @return A unique pointer to the initialized timer driver interface.
 */
std::unique_ptr<timer::Interface> Esp32s3::timer(std::uint32_t timeout_ms) noexcept {

    auto t = std::make_unique<driver::timer::Esp32s3>();
    t->setPeriod(timeout_ms);
    return t;
}

} // namespace driver::factory
