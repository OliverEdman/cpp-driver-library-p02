/**
 * @file Tmp36.h
 * @brief Real driver implementation for the TMP36 temperature sensor.
 */

#pragma once

#include "driver/tempsensor/interface.h"
#include "driver/adc/interface.h"


namespace driver::tempsensor {


/**
 * @class Tmp36
 * @brief TMP36 temperature sensor driver using ADC Dependency Injection.
 *
 * Implements the temperature interface by converting analog voltage readings
 * from an injected ADC instance into Celsius degrees.
 */

class Tmp36 final : public Interface {
public:



     /**
     * @brief Constructor.
     * @param adc Reference to the ADC interface used to get sensor voltage.
     */

   explicit Tmp36(driver::adc::Interface& adc, std::uint8_t pin) noexcept; 

    /**
     * @brief Destructor.
     */

    ~Tmp36() noexcept override = default;

    /**
     * @brief Reads the current temperature from the hardware.
     * * Converts the analog voltage read from the ADC into degrees Celsius
     * Using (Voltage - 0.5V) * 100.
     * * @return Current temperature in degrees Celsius.
     */
    float readCelsius() noexcept override;

    /**
     * @brief Checks if the temperature sensor is ready to be used.      
     * @return true if initialized and ready, false otherwise.
     */
    bool isInitialized() const noexcept override;

    // Disable Copy and Move operations
    Tmp36(const Tmp36&)            = delete;
    Tmp36& operator=(const Tmp36&) = delete;
    Tmp36(Tmp36&&)                 = delete;
    Tmp36& operator=(Tmp36&&)      = delete; 

private:
    /** 
     * @brief Reference to the injected ADC interface. 
     */

    driver::adc::Interface& myAdc;
    std::uint8_t myPin;
};

} // namespace driver::tempsensor
