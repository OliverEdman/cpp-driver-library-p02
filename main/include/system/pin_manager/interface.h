#pragma once

#include <cstdint>

namespace system::pin_manager
{
class Interface
{
public:
    virtual ~Interface() noexcept = default;

    /**
     * @brief Check if pin is being used.
     * 
     * @param[in] pin Corresponding bit to check in PinRegister.
     * 
     * @return True if free, false if busy or invalid.
     */
    virtual bool isPinBusy(std::uint8_t pin) const noexcept = 0;

    /**
     * @brief Reserve pin.
     * 
     * @param[in] pin Corresponding bit to reserve in PinRegister
     * @return True on success, false otherwise.  
     */
    virtual bool reservePin(std::uint8_t pin) noexcept = 0;

    /**
     * @brief Release pin.
     * 
     * @param[in] pin Corresponding bit to release in PinRegister
     */
    virtual void releasePin(std::uint8_t pin) noexcept = 0;
};
} // namespace system::pin_manager
