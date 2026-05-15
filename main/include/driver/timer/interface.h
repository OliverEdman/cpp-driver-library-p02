#pragma once
#include <cstdint>


namespace driver::timer {

/**
 * @class Interface
 * @brief Abstract interface for a Timer driver.
 */

class Interface {
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~Interface() = default;
    
    /**
     * @brief Starts the timer.
     */
    virtual void start() = 0;

    /**
     * @brief Stops the timer.
     */
    virtual void stop() = 0;
    
    /**
     * @brief Sets the timer period in milliseconds.
     * * @param[in] period_ms The alarm period in milliseconds.
     */
    virtual void setPeriod(std::uint32_t period_ms) = 0;
    
    /**
     * @brief Indicates whether a timeout has occurred since the last call.
     * * @return true if a timeout occurred, false otherwise.
     */
    virtual bool isTimeout() = 0; 

    /**
     * @brief Checks if the timer hardware is successfully initialized.
     * * @return true if initialized and ready for use, false otherwise.
     */
    virtual bool isInitialized() const = 0;
};

} // namespace driver::timer
