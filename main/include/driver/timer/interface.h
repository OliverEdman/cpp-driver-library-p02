/**
 * @brief Timer driver interface
 */

#pragma once

#include <cstdint>

namespace driver::timer
{

/**
* @brief Timer driver interface. 
*/

class Interface
{
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~Interface() noexcept = default;

    /**
     * @brief Check if the timer is initialized.
     * @return True if initialized, false otherwise.
     */
    virtual bool isInitialized() const noexcept = 0;

    /**
     * @brief Get the current timeout.
     * @return Timeout in milliseconds.
     */
    virtual std::uint32_t timeout_ms() const noexcept = 0;

    /**
     * @brief Sets the timer timeout period.
     * @param[in] period_ms Timeout duration in milliseconds.
     */
    virtual void setPeriod(std::uint32_t period_ms) noexcept = 0;

    /**
     * @brief Start timer.
     */
    virtual void start() noexcept = 0;

    /**
     * @brief Stop timer.
     */
    virtual void stop() noexcept = 0;

    /**
     * @brief Check if the timer is running.
     * @return True if the timer is running, false otherwise.
     */
    virtual bool isRunning() const noexcept = 0;

    /**
     * @brief Toggle the timer state (start/stop).
     */
    virtual void toggle() noexcept = 0;
  
};
} // namespace driver::timer
