#pragma once
#include "interface.h"


namespace driver::timer {

/**
 * @class Stub
 * @brief Simulation implementation of the Timer interface.
 * * This class is used for unit testing system logic without requiring 
 * actual ESP32-S3 hardware.
 */
class Stub : public Interface {
public:
    /**
     * @brief Constructor sets stub variables.
     */
    Stub() : my_running(false), my_timeout(false), my_period(0) {}

    /**
     * @brief Virtual destructor.
     */
    virtual ~Stub() noexcept override = default;

    /** @brief Simulates starting the timer. */
    void start() noexcept override {
	    my_running = true;
    }

    /** @brief Simulates stopping the timer. */
    void stop() noexcept override {
	    my_running = false;
    }

    /** * @brief Sets the simulated period.
     * @param[in] period_ms Period in milliseconds.
     */
    void setPeriod(std::uint32_t period_ms) noexcept override {
	    my_period = period_ms;
    }

    /** * @brief Returns the simulated timeout state and resets it.
     */
    bool isTimeout() noexcept override {
        bool result = my_timeout;
        my_timeout = false; // Reset on read to match real driver behavior
        return result;
    }

    /** * @brief Stubs are always considered initialized.
     */
    bool isInitialized() const noexcept override {
	    return true;
    }
    
    /**
     * @brief Manually triggers a timeout for testing purposes.
     */
    void simulateTimeout() noexcept {
	    my_timeout = true;
    }

    /**
     * @brief Checks if the timer is currently "running".
     */
    bool isRunning() const noexcept {
	    return my_running;
    }

    /**
     * @brief Gets the current period set in the stub.
     */
    std::uint32_t getPeriod() const noexcept {
	    return my_period;
    }

private:
    bool my_running;
    bool my_timeout;
    std::uint32_t my_period;
};

} // namespace driver::timer
