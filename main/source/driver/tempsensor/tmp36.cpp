/**
 * @file Tmp36.cpp
 * @brief Implementation of the TMP36 temperature sensor driver.
 */

#include "driver/tempsensor/tmp36.h"
#include "esp_log.h"

namespace driver::tempsensor {

/**
 * @brief Constructor. When Tmp36 instance is created we force to bind it to ADC interface.
 */
Tmp36::Tmp36(driver::adc::Interface& adc, std::uint8_t pin) noexcept 
    : myAdc{adc}
    , myPin{pin}
{
    // The reference to the ADC interface is located in the initializier list above, with the . operator we can use adc functions to get celsius from voltage. 
}

/**
 * @brief get the voltage and converts it to Celsius.
 */
float Tmp36::readCelsius() noexcept {
    // we use myAdc to get voltage from adc interface 
    const float voltage = myAdc.readVoltage();

    // Convert voltage to Celsius using the the following formula:
    // (Voltage - 500mV offset) * 100 degrees/V
    // Tmp36 have a offset of 0.5v so we must subtract 0.5V from the output voltage. (500mV)
    const auto temp = (voltage - 0.5f) * 100.0f;

    ESP_LOGI("TMP36", "Temperature: %f", temp);
    return temp;
}

/**
 * @brief Checks if the ADC is initialized.
 */
bool Tmp36::isInitialized() const noexcept {
    // The TMP36 sensor is considered ready if the ADC is running
    return myAdc.isInitialized();
}

} // namespace driver::tempsensor
