#pragma once

#include "driver/timer/interface.h"
#include "driver/gptimer.h" // esp-idf gptimer
#include <cstdint>

namespace driver::timer
{

	/**
	 * @brief Hardware implementation of the Timer for ESP32-S3.
	 ** This class implements the Timer Interface using the ESP-IDF GPtimer peripheral.
	 */

class Esp32s3 final : public Interface
{
public:

	/**
	 *  @brief Constructor. Initialize the GPTimer hardware.
	 */
    Esp32s3();
	
    	/**
	 * @brief Destructor. Disables hardware and releases rescources to prevent memory leaks.
	 */
    ~Esp32s3() noexcept override;


	// Interface implementations.
    /** @brief Returns true if the timer has been succuessfully initialized. */
    bool isInitialized() const noexcept override;

    /** @brief Returns the current timeout period in milliseconds. */
    std::uint32_t timeout_ms() const noexcept override;

    /** @brief Configures the timer alarm period in milliseconds.*/
    void setPeriod(std::uint32_t period_ms) noexcept override;

    /** @brief Starts the hardware timer counter. */
    void start() noexcept override;

    /** @brief Stops the hardware timer counter.*/
    void stop() noexcept override;

    /** @brief Checks if the timer is currently running. */
    bool isRunning() const noexcept override;

    /** @brief Toggles the timer between running and stopped states. */
    void toggle() noexcept override;

    /** @brief Checks if a timeout event has ocurred since the last check. */
    bool isTimeout() noexcept override;

private: 
    /**
     *  @brief This function configure the ESP-IDF GPtimer settings.
    */
    void timer_init();

    // ESP-IDF specific handle for timer.
    gptimer_handle_t my_timer_handle{nullptr};

    //state variables to track driver status.
    bool my_is_initialized{false};
    bool my_is_running{false};
    std::uint32_t my_period_ms{0};

    /** @brief Flag set by the Interrupt Serivce Routine (ISR) when a timeout occurs. */
    volatile bool my_is_timeout_triggered{false};

    /**
     * @brief Static callback function called by the hardware on alarm events.
     */
    static bool IRAM_ATTR timer_callback(gptimer_handle_t timer,
		    			const gptimer_alarm_event_data_t *edata,
					void *user_ctx);

};

} // namespace driver::timer
