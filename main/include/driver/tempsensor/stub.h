/**
 * @brief Temperature sensor driver stub for simulation.
 */
#pragma once

//! @remark This file won't compiler, please fix the variable naming when you have time!

//! @note Include path is missing the driver prefix => driver/tempsensor/interface.h.
#include "tempsensor/interface.h"

namespace driver::tempsensor
{
/**
 * @brief Temperature sensor driver stub for simulation.
 * 
 *        This class simulates temperature readings in memory without real hardware.
 *        This class cannot be copied or moved.
 */
class Stub final : public Interface
{
public:
    /**
     * @brief Constructor.
     */
    //! @note 'my_simulatedTemp' should be mySimulatedTemp and 'my_initialized' should be myInitialized.
    //! For this reason, this code will not compile.
    Stub() noexcept
	    : my_simulatedTemp{25.0f}
        , my_initialized{true}
    {}

    /**
     * @brief Destructor.
     */
    ~Stub() noexcept override = default;

    // Delete copy/move constructors and operators.
    Stub(const Stub&)            = delete;
    Stub& operator=(const Stub&) = delete;
    Stub(Stub&&)                 = delete;
    Stub& operator=(Stub&&)      = delete;

    //! @note Imperative comment => "Read" instead of "Reads".
    /**
     * @brief Reads the current simulated temperature.
     * 
     * @return The simulated temperature value in degrees Celsius.
     */
    float readCelsius() noexcept override { return my_simulatedTemp; }

    //! @note Imperative comment => "Check" instead of "Checks".
    /**
     * @brief Checks if the simulated sensor driver is successfully initialized.
     * 
     * @return True if initialized, false otherwise.
     */
    bool isInitialized() const noexcept override { return my_initialized; }

    /**
     * @brief Set the simulated temperature value that the stub should return.
     * 
     * @param[in] temp The target temperature in degrees Celsius.
     */
    void setTemperature(float temp) noexcept { my_simulatedTemp = temp; }

    //! @note Imperative comment => "Set" instead of "Sets".
    /**
     * @brief Sets the initialization state of the stub.
     * 
     * @param[in] state Set to true to simulate an initialized sensor, false otherwise.
     */
    void setInitialized(bool state) noexcept { my_initialized = state; }

private:
    //! @note You may skip @brief for one-line comments.
    /** @brief The currently stored simulated temperature value. */
    float mySimulatedTemp;

    /** @brief The currently stored simulated initialization state. */
    bool myInitialized;
};
} // namespace driver::tempsensor
