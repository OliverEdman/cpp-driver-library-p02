/**
 * @brief Temperature sensor driver stub for simulation.
 */

#pragma once
#include "tempsensor/interface.h"

namespace driver::tempsensor {

/**
 * @brief Temperature sensor driver stub for simulation.
 * This class simulates temperature readings in memory without real hardware.
 * This class cannot be copied or moved.
 */
class Stub final : public Interface {
public:

    /**
     * @brief Constructor.
     */
    Stub() noexcept 
	    : mySimulatedTemp{25.0f}
            , myInitialized{true}
{

}


    /**
     * @brief Destructor.
     */
    ~Stub() noexcept override = default;

    // Delete copy/move constructors and operators.
    Stub(const Stub&)            = delete;
    Stub& operator=(const Stub&) = delete;
    Stub(Stub&&)                 = delete;
    Stub& operator=(Stub&&)      = delete;

    /**
     * @brief Read the current simulated temperature.
	 *
     * @return The simulated temperature value in degrees Celsius.
     */
	float readCelsius() noexcept override { return mySimulatedTemp; }

    /**
     * @brief Check if the simulated sensor driver is successfully initialized.
	 *
     * @return True if initialized, false otherwise.
     */
    bool isInitialized() const noexcept override { return myInitialized; }

    /**
     * @brief Set the simulated temperature value that the stub should return.
	 *
     * @param[in] temp The target temperature in degrees Celsius.
     */
    void setTemperature(float temp) noexcept { mySimulatedTemp = temp; }

    /**
     * @brief Sets the initialization state of the stub.
	 *
     * @param[in] state Set to true to simulate an initialized sensor, false otherwise.
     */
    void setInitialized(bool state) noexcept {
        myInitialized = state;
    }

private:
    /** The currently stored simulated temperature value. */
    float mySimulatedTemp;

    /** The currently stored simulated initialization state. */
    bool myInitialized;
};

} // namespace driver::tempsensor
