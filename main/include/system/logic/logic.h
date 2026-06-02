/**
 * @file logic.h
 * @brief Declaration of the Logic class.
 * @author Oliver Edman
 */

#pragma once

#include "driver/factory/interface.h"

#include <atomic>
#include <memory>
#include <cstdint>

namespace app::logic {

/**
 * @class Logic
 * @brief Main system logic class.
 *
 * This class contains the application logic for the system.
 * It communicates only with driver interfaces and does not
 * know anything about ESP-IDF or hardware specific code.
 *
 * The class controls:
 *  LED behavior
 *  Serial commands
 *  Timer based blinking
 *  Temperature reading
 */
class Logic final {
public:

    /**
     * @brief The constructor uses the factory to create all drivers needed by the system.
     * @param[in] factory Reference to a driver factory.
     */
    explicit Logic(driver::factory::Interface& factory) noexcept;

    /**
     * @brief Destructor used to clean up the logic class safely.
     */
    ~Logic() noexcept;

    /**
     * @brief Start the main loop.
     *
     * The loop runs until the stop flag becomes true.
     *
     * @param[in] stop Atomic flag used to stop the system safely.
     */
    void run(const std::atomic<bool>& stop) noexcept;

    /**
     * @brief Disable copy operations.
     *
     * The logic class owns hardware drivers through
     * std::unique_ptr and should not be copied or moved.
     */
    Logic(const Logic&) = delete;
    Logic& operator=(const Logic&) = delete;
    Logic(Logic&&) = delete;
    Logic& operator=(Logic&&) = delete;

private:

    /**
     * @brief Set the default startup state.
     *
     * Startup state = LED OFF and Blink mode disabled.
     */
    void setStartState() noexcept;

    /**
     * @brief Initiate drivers
     * 
     *  Initiates neccesiray drivers.
     */
    void initializeDrivers() noexcept;

    /**
     * @brief Read and process serial input.
     *
     * Reads commands from the serial driver and forwards
     * them to the command handler.
     */
    void processSerial() noexcept;

    /**
     * @brief Handle timer events.
     *
     * Toggles the LED when blink mode is active
     * and the timer has timed out.
     */
    void processTimer() noexcept;

    /**
     * @brief Execute serial commands.
     *
     * Supported commands are on,off,blink on/off, period <value>, status and temp.
     * @param[in] command Command string from serial input.
     */
    void handleCommand(const char* command) noexcept;

    /**
     * @brief Print current system status.
     *
     * Prints blink state, blink period and current temperature.
     */
    void printStatus() noexcept;

    /**
     * @brief Print the current temperature.
     */
    void printTemperature() noexcept;

    /**
     * @brief Driver interfaces used by the logic class.
     *
     * The logic class uses these pointers to communicate
     * with the hardware drivers through their interfaces.
     */ 

    // Serial communication driver.
    std::unique_ptr<driver::serial::Interface> mySerial;

    // GPIO driver used for LED control.
    std::unique_ptr<driver::gpio::Interface> myLed;

    // Timer driver used for blink timing.
    std::unique_ptr<driver::timer::Interface> myTimer;

    // ADC driver used by the temperature sensor.
    std::unique_ptr<driver::adc::Interface> myAdc;

    // Temperature sensor driver.
    std::unique_ptr<driver::tempsensor::Interface> myTempSensor;

    // True when blink mode is enabled.
    bool myBlinkEnabled{false};

    // Current LED blink period in milliseconds.
    std::uint32_t myPeriodMs{500U};
};

} // namespace app::logic
