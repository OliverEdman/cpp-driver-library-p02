#pragma once

#include <cstdint>

#include "driver/timer/interface.h"
#include "driver/gptimer.h"
#include "esp_attr.h"

namespace driver::timer {

/**
 * @brief Real hardware interface for the ESP32-S3 timer driver.
 *
 * This class configures and controls a hardware General Purpose Timer (GPTimer).
 * This class cannot be copied or moved.
 */
class Esp32s3 final : public Interface
{
public:
    /**
     * @brief Constructor that initializes the GPTimer hardware.
     */
    Esp32s3() noexcept;

    /**
     * @brief Destructor that ensures hardware resources are released.
     */
    ~Esp32s3() noexcept override = default;

    /** Start the ESP32-S3 hardware timer. */
    void start() noexcept override;

    /** Stop the ESP32-S3 hardware timer. */
    void stop() noexcept override;

    /**
     * @brief Configure the alarm value based on milliseconds.
     *
     * @param[in] periodMs Period in milliseconds.
     */
    void setPeriod(std::uint32_t periodMs) noexcept override;

    /**
     * @brief Check if the hardware timer has triggered an interrupt.
     *
     * @return True if a timeout has occurred, false otherwise.
     */
    bool isTimeout() noexcept override;

    /**
     * @brief Check the initialization status of the GPTimer.
     *
     * @return True if initialized, false otherwise.
     */
    bool isInitialized() const noexcept override;

    // Delete copy/move operations
    Esp32s3(const Esp32s3&)            = delete;
    Esp32s3& operator=(const Esp32s3&) = delete;
    Esp32s3(Esp32s3&&)                 = delete;
    Esp32s3& operator=(Esp32s3&&)      = delete;

private:
    /** Driver handle for the ESP-IDF GPTimer instance. */
    gptimer_handle_t myHandle{nullptr};

    /** Interrupt flag set by the ISR when the timer alarms. */
    volatile bool myTimeoutFlag{false};

    /** Flag tracking if the hardware timer is successfully initialized. */
    bool myInitialized{false};

    /**
     * @brief ISR callback function triggered on timer alarm events.
     *
     * @param[in] timer    Handle to the timer.
     * @param[in] event    Pointer to the alarm event data.
     * @param[in] userData User-provided context.
     *
     * @return True if a high-priority task was woken.
     */
    static bool IRAM_ATTR timerCallback(gptimer_handle_t timer,
                                        const gptimer_alarm_event_data_t *event,
                                        void *userData);
};
} // namespace driver::timer
