#pragma once
#include "interface.h"
#include "driver/gptimer.h"
#include "esp_attr.h"

namespace driver::timer {

/**
 * @class Esp32s3
 * @brief Real hardware implementation of the Timer interface for ESP32-S3.
 */
class Esp32s3 : public Interface {
public:
    /**
     * @brief Constructor that initializes the GPTimer hardware.
     */
    Esp32s3() noexcept;

    /**
     * @brief Destructor that ensures hardware resources are released.
     */
    virtual ~Esp32s3() noexcept;

    /** @brief Starts the ESP32-S3 hardware timer. */
    void start() noexcept override;

    /** @brief Stops the ESP32-S3 hardware timer. */
    void stop() noexcept override;

    /** * @brief Configures the alarm value based on milliseconds. 
     * @param[in] period_ms Period in milliseconds.
     */
    void setPeriod(std::uint32_t period_ms) noexcept override;

    /** * @brief Returns true if the hardware timer has triggered an interrupt. 
     */
    bool isTimeout() noexcept override;
    
    /** * @brief Returns the initialization status of the GPTimer. 
     */
    bool isInitialized() const noexcept override;

private:
    gptimer_handle_t handle = nullptr;
    volatile bool timeout_flag = false;
    bool my_initialized = false;
    
    /**
     * @brief ISR callback.
     */
    static bool IRAM_ATTR timer_callback(gptimer_handle_t timer, 
                                        const gptimer_alarm_event_data_t *edata, 
                                        void *user_data);
};

} // namespace driver::timer
