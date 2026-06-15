/**
 * @brief Real hardware interface for the ESP32-S3 timer driver.
 */
#pragma once

//! @note Include <cstdint>

//! @note Please don't use relative paths: use "driver/timer/interface.h".
#include "interface.h"

#include "driver/gptimer.h"
#include "esp_attr.h"

namespace driver::timer {

/**
 * @brief Real hardware interface for the ESP32-S3 timer driver.
 * This class configures and control a hardware Genreal Purpose Timer (GPTimer)
 //! @note Typos: "control" → "controls", "Genreal" → "General".
 * This class cannot be copied or moved.
 */
class Esp32s3 final : public Interface
{
public:
    //! @note Should be moved to the bottom of the public segment.
    Esp32s3(const Esp32s3&)            = delete;
    Esp32s3& operator=(const Esp32s3&) = delete;
    Esp32s3(Esp32s3&&)                 = delete;
    Esp32s3& operator=(Esp32s3&&)      = delete;

    /**
     * @brief Constructor that initializes the GPTimer hardware.
     */
    Esp32s3() noexcept;

    /**
     * @brief Destructor that ensures hardware resources are released.
     */
    //! @note Don't write virtual when the class is final and override is implied.
    //!       Write override instead => ~Esp32s3() noexcept override;
    virtual ~Esp32s3() noexcept;

    //! @note Use imperative comments => "start", "stop", "configures etc.".
    /** @brief Starts the ESP32-S3 hardware timer. */
    void start() noexcept override;

    /** @brief Stops the ESP32-S3 hardware timer. */
    void stop() noexcept override;

    /** 
     * @brief Configures the alarm value based on milliseconds. 
     * 
     * @param[in] period_ms Period in milliseconds.
     */
    void setPeriod(std::uint32_t period_ms) noexcept override;

    /** 
     * @brief Check if the hardware timer has triggered an interrupt (timeout).
     * 
     * @return True if a timeout has occured, false otherwise.
     */
    bool isTimeout() noexcept override;

    /** 
     * @brief Check the initialization status of the GPTimer.
     * 
     * @return True if initialized, false otherwise.
     */
    bool isInitialized() const noexcept override;

private:
    //! @note You may skip @brief for one-line comments.
    //! @note Use camelCase (myInitialized), not snake_case (my_initialized).
    //!       Also, don't forget prefix 'my' (myHandle, myTimeoutFlag).
    //! @note Use brace initialisation if initializing member variables in the class.
    //!       Still I would prefer using constructors for a class.

    /** @brief Driver handle for the ESP-IDF GPTimer instance. */
    gptimer_handle_t handle = nullptr;

    /** @brief Interrupt flag set by the ISR when the timer alarms. */
    volatile bool timeout_flag = false;

    /** @brief Flag tracking if the hardware timer is successfully initialized. */
    bool my_initialized = false;
    
     /** @brief ISR callback function triggered on timer alarm events. */
     //! @note This method should be named timerCallback, callback or something (camelCase).
     //!       And user_data shoule be called userData.
    static bool IRAM_ATTR timer_callback(gptimer_handle_t timer, 
                                        const gptimer_alarm_event_data_t *edata, 
                                        void *user_data);
};
} // namespace driver::timer
