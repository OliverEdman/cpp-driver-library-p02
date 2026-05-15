/**
 * @file Stub.h
 * @brief Stub implementation of the temperature sensor interface for simulation and testing.
 */

#pragma once
#include <cstdint>
#include "tempsensor/interface.h"

namespace driver::tempsensor {

/**
 * @class Stub
 * @brief Simulation class for a temperature sensor.
 */
class Stub : public Interface {
public:

    /**
     * @brief Default constructor.
     */
    Stub() = default;

    /**
     * @brief Virtual destructor.
     */
    virtual ~Stub() = default;

    /**
     * @brief Reads the currently set simulated temperature.
     * @return The simulated temperature in Celsius.
     */
    float readCelsius() noexcept override {
        return my_simulatedTemp;
    }

    /**
     * @brief Checks if the simulated sensor is initialized.
     * @return true if the stub is initialized,false otherwise.
     */
    bool isInitialized() const noexcept override {
        return my_initialized;
    }

    /** @brief Simulation Functions
     * These functions are unique to the Stub class and are used for tests. 
     */

    /**
     * @brief Sets the temperature that the stub should return.
     */
    void setTemperature(float temp) noexcept {
        my_simulatedTemp = temp;
    }

    /**
     * @brief Sets the initialization state of the stub.
     * @param state The state to set (true for initialized, false for not).
     */
    void setInitialized(bool state) noexcept {
        my_initialized = state;
    }

private:
    float my_simulatedTemp = 25.0f; // Simulated temperature 
    bool my_initialized = true;     // Simulated initialization state.
};

} // namespace driver::tempsensor
