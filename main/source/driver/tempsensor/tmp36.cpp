//! @note Missing file header.

//! @note Include <cstdint> and driver/adc/interface.h

#include "driver/tempsensor/tmp36.h"

namespace driver::tempsensor
{
// -----------------------------------------------------------------------------
Tmp36::Tmp36(driver::adc::Interface& adc, std::uint8_t pin) noexcept
    : myAdc{adc}
    , myPin{pin}
{}

// -----------------------------------------------------------------------------
float Tmp36::readCelsius() noexcept {
    //! @note Avoid first-person "we" in comments. Please write imperative 
    //!       => "Read voltage from the ADC." Same for the 'temp' comment below.
    // we use myAdc to get voltage from adc interface
    //! @note You may also use auto here.
    const float voltage = myAdc.readVoltage();

    // Convert voltage to Celsius using the the following formula:
    // (Voltage - 500mV offset) * 100 degrees/V
    // Tmp36 have a offset of 0.5v so we must subtract 0.5V from the output voltage. (500mV)
    const auto temp = (voltage - 0.5f) * 100.0f;

    //! @note 'temp' can be omitted, you can return (voltage - 0.5f) * 100.0f directly.
    return temp;
}

// -----------------------------------------------------------------------------
bool Tmp36::isInitialized() const noexcept
{
    // The TMP36 sensor is considered ready if the ADC is running.
    return myAdc.isInitialized();
}
} // namespace driver::tempsensor
