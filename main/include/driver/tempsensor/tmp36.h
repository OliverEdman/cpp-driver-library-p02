/**
 * @file tmp36.h
 * @brief Real driver interface for the TMP36 temperature sensor.
 */

#pragma once

#include "driver/tempsensor/interface.h"
#include "driver/adc/interface.h"


namespace driver::tempsensor {


/**
 * @brief TMP36 temperature sensor driver using ADC Dependency Injection.
 * Implements the temperature interface by converting analog voltage readings
 * from an injected ADC instance into Celsius degrees.
 * This class cannot be copied or moved.
 */
class Tmp36 final : public Interface {
public:
     /**
     * @brief Constructor.
     * @param[in] adc Reference to the ADC interface used to get sensor voltage.
     * @param[in] pin the specific ADC pin/channel number of the sensor is connected to.
     */
   explicit Tmp36(driver::adc::Interface& adc, std::uint8_t pin) noexcept; 

    /**
     * @brief Destructor.
     */
    ~Tmp36() noexcept override = default;

    /**
     * @brief Read the current temperature from the hardware.
     * Converts the analog voltage read from the ADC into degrees Celsius
     * Using the formula: (Voltage - 0.5V) * 100.
     * @return The current temperature value in degrees Celsius.
     */
    float readCelsius() noexcept override;

    /**
     * @brief Check if the temperature sensor is ready to be used.      
     * @return True if initialized and ready, false otherwise.
     */
    bool isInitialized() const noexcept override;

    // Delete copy/move constructors and operators.
    Tmp36(const Tmp36&)            = delete;
    Tmp36& operator=(const Tmp36&) = delete;
    Tmp36(Tmp36&&)                 = delete;
    Tmp36& operator=(Tmp36&&)      = delete; 

private:
    /** @brief Refrence to the injected ADC interface.*/
    driver::adc::Interface& myAdc;

    /** @brief The hardware pin number assigned to this sensor*/
    std::uint8_t myPin;
};

} // namespace driver::tempsensor
