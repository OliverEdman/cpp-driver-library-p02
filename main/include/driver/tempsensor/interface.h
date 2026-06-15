/**
 * @brief Interface for the temperature driver.
 */
#pragma once 

namespace driver::tempsensor
{
/**
 * @brief Abstract interface for temperature sensor driver.
 */
class Interface
{
public:
    /**
     * @brief Destructor.
     */
    virtual ~Interface() noexcept = default;
	
    /**
     * @brief Read the current temperature from the sensor.
     * 
     * @return The temperature value in degrees Celsius.
     */
    virtual float readCelsius() noexcept = 0;

    //! @note Write imperative => use "Check if" instead of "Checks if".
    //!       Also "succuessfully" should be "successfully" and "oterwise" should be
    //!       "otherwise", but OK. :)
    /**
     * @brief Checks if the temperature sensor driver is succuessfully initialized.
     * 
     * @return true if initialized and ready, false oterwise.
     */
    virtual bool isInitialized() const noexcept = 0;
};
} // namespace driver::tempsensor
