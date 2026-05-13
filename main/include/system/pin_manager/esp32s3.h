#pragma once

#include <cstdint>

#include "system/pin_manager/interface.h"

namespace system::pin_manager
{
class Esp32s3 final : public Interface
{
public:
    /**
     * @brief Return singleton ESP32-s3 pin manger instance.
     */
    static Interface& instance() noexcept;

    /**
     * @brief Check if pin is valid.
     * 
     * @param[in] pin Corresponding bit to check in PinRegister.
     * 
     * @return True if valid, otherwise false.
     */
    bool isPinValid(std::uint8_t pin) const noexcept override;

    /**
     * @brief Check if pin is being used.
     * 
     * @param[in] pin Corresponding bit to check in PinRegister.
     * 
     * @return True if free, false if busy or invalid.
     */
    bool isPinBusy(std::uint8_t pin) const noexcept override;

    /**
     * @brief Reserve pin.
     * 
     * @param[in] pin Corresponding bit to reserve in PinRegister
     * @return True on success, false otherwise.  
     */
    bool reservePin(std::uint8_t pin) noexcept override;

    /**
     * @brief Release pin.
     * 
     * @param[in] pin Corresponding bit to release in PinRegister
     */
    void releasePin(std::uint8_t pin) noexcept override;

    Esp32s3(const Esp32s3&)            = delete;
    Esp32s3(Esp32s3&&)                 = delete;
    Esp32s3& operator=(const Esp32s3&) = delete;
    Esp32s3& operator=(Esp32s3&&)      = delete;


private:
    Esp32s3() noexcept;
    ~Esp32s3() noexcept override = default;

    std::uint64_t myPinReg;
};
} // namespace system::pin_manager
