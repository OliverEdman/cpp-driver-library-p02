#pragma once 

namespace driver::tempsensor {

/**
 * @class Interface
 * @brief Abstraction for a temperature sensor driver.
 */
class Interface {
public:

    /**
    * @brief Virtual destructor.
    */

    virtual ~Interface() noexcept = default;
	
    /**
     * @brief Read the current temperature.
     * @return Temperature in degrees Celsius.
     */

    virtual float readCelsius() noexcept = 0;

    /**
     * @brief Checks if the sensor driver is succuessfully initialized.
     * @return true if initialized, false oterwise.
     */

    virtual bool isInitialized() const noexcept = 0;
};

} // namespace driver::tempsensor

