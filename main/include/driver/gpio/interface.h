/**
 * @brief GPIO driver interface
 */
#pragma once

#include <cstdint>
#include <cstdio>

namespace driver::gpio
{
/**
 * @brief GPIO driver interface
 */
class Interface
{
public:
    /**
     * @brief Destructor
     */
    virtual ~Interface() noexcept = default;

    /**
     * @brief Write GPIO state.
     * 
     * @param[in] state True to enable the GPIO, false otherwise.
     */
    virtual void write(bool state) noexcept = 0;

    /**
     * @brief Read GPIO state.
     * 
     * @return True if the GPIO is active/high, false otherwise.
     */
    virtual bool read() const noexcept = 0;

    /**
     * @brief toggle the GPIO.
     */
    virtual void toggle() noexcept = 0;
    
};
} // namespace driver::gpio