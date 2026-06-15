/**
 * @brief Declaration of the Logic class.
 * 
 * @author Oliver Edman
 */
#pragma once

//! @note Include standard headers first.
#include "driver/factory/interface.h"

//! @note Sort headers.
#include <atomic>
#include <memory>
#include <cstdint>

#include "sdkconfig.h"

namespace app::logic
{
/**
 * @brief Main system logic class.
 *
 *        This class contains the application logic for the system.
 *        It communicates only with driver interfaces and does not
 *        know anything about ESP-IDF or hardware specific code.
 *
 *        The class controls:
 *            - LED behavior
 *            - Serial commands
 *            - Timer based blinking
 *            - Temperature reading
 */
class Logic final
{
public:
    /**
     * @brief Constructor.
     * 
     * @param[in] factory Factory to create all drivers needed by the system.
     */
    explicit Logic(driver::factory::Interface& factory) noexcept;

    /**
     * @brief Destructor used to clean up the logic class safely.
     */
    ~Logic() noexcept;

    /**
     * @brief Start the main loop.
     * 
     *        Run until the stop flag becomes true.
     * 
     * @param[in] stop Atomic flag used to stop the system safely.
     */
    void run(const std::atomic<bool>& stop) noexcept;

    /** Disable copy operations. */
    Logic() = delete;
    Logic(const Logic&) = delete;
    Logic& operator=(const Logic&) = delete;
    Logic(Logic&&) = delete;
    Logic& operator=(Logic&&) = delete;

private:
    /**
     * @brief Set the default startup state.
     * 
     *        Startup state = LED OFF and Blink mode disabled.
     */
    void setStartState() noexcept;

    /**
     * @brief Initialize drivers.
     * 
     *        Initialize the necessary drivers required by the system.
     */
    void initializeDrivers() noexcept;

    /**
     * @brief Read and process serial input.
     * 
     *        Read commands from the serial driver and forwards them to the command handler.
     */
    void processSerial() noexcept;

#if CONFIG_P02_ENABLE_MQTT
    /**
     * @brief Read and process MQTT commands.
     *
     *        Read incoming MQTT payloads and forwards them to the shared
     *        command handler used by the serial interface.
     */
    void processMqtt() noexcept;
#endif // CONFIG_P02_ENABLE_MQTT

    /**
     * @brief Handle timer events.
     *
     *        Toggle the LED when blink mode is active and the timer has timed out.
     */
    void processTimer() noexcept;

    /**
     * @brief Execute system commands.
     * 
     *        Supported commands are on, off, blink on/off, period <value>, status and temp.
     * 
     * @param[in] command Command string received from Serial or MQTT.
     */
    void handleCommand(const char* command) noexcept;

    /**
     * @brief Print current system status.
     * 
     *        Print blink state, blink period, and current temperature.
     */
    void printStatus() noexcept;

    /**
     * @brief Print the current temperature.
     */
    void printTemperature() noexcept;

    /** Serial communication driver interface pointer. */
    std::unique_ptr<driver::serial::Interface> mySerial;

    /** GPIO driver interface pointer used for LED control. */
    std::unique_ptr<driver::gpio::Interface> myLed;

    /** Timer driver interface pointer used for blink timing. */
    std::unique_ptr<driver::timer::Interface> myTimer;

    /** ADC driver interface pointer used by the temperature sensor. */
    std::unique_ptr<driver::adc::Interface> myAdc;

    /** Temperature sensor driver interface pointer. */
    std::unique_ptr<driver::tempsensor::Interface> myTempSensor;

#if CONFIG_P02_ENABLE_MQTT
    /** WiFi driver interface pointer used before MQTT networking. */
    std::unique_ptr<driver::wifi::Interface> myWifi;

    /** MQTT driver interface pointer used by the P02+ integration. */
    std::unique_ptr<driver::mqtt::Interface> myMqtt;
#endif // CONFIG_P02_ENABLE_MQTT

    /** Flag tracking whether blink mode is currently enabled. */
    bool myBlinkEnabled{false};

    /** Current LED blink period config in milliseconds. */
    std::uint32_t myPeriodMs{500U};

#if CONFIG_P02_ENABLE_MQTT
    /** Flag tracking whether the MQTT command topic subscription is active. */
    bool myMqttSubscribed{false};
#endif // CONFIG_P02_ENABLE_MQTT
};
} // namespace app::logic
