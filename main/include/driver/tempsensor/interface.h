/**
 * @file interface.h
 * @brief Interface for the temperature driver.
 */

#pragma once 

namespace driver::tempsensor {

/**
 * @brief Abstract interface for temperature sensor driver.
 */
class Interface {
public:

    /**
    * @brief Virtual destructor.
    */

    virtual ~Interface() noexcept = default;
	
    /**
     * @brief Read the current temperature from the sensor.
     * @return The temperature value in degrees Celsius.
     */

    virtual float readCelsius() noexcept = 0;

    /**
     * @brief Checks if the temperature sensor driver is succuessfully initialized.
     * @return true if initialized and ready, false oterwise.
     */

    virtual bool isInitialized() const noexcept = 0;
};

} // namespace driver::tempsensor

