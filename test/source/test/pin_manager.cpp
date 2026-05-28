#include <cstdio>

#include "system/pin_manager/interface.h"
#include "test/pin_manager.h"

namespace test
{
bool runPinManagerTest(sys::pin_manager::Interface& manager) noexcept
{
    constexpr std::uint8_t pinMax{100U};

    // Check every pin number one by one.
    for (std::uint8_t pin{}; pin < pinMax; ++pin)
    {
        // Check if pin is valid.
        const bool valid{manager.isPinValid(pin)};
        
        // Expect the pin to be reservable if it's available and valid.
        const bool reserved{manager.isPinBusy(pin)};

        // Try to reserve, check sttus.
        const bool reserveSucceeded{manager.reservePin(pin)};

        // If valid, expect the pin reservation to succeed if the pin wasn't reserved.
        if (valid)
        {
            const bool success{reserved != reserveSucceeded};

            if (!success)
            {
                std::printf("Reservation of pin %u failed: reserved = %d, reserveSucceeded = %d\n",
                            pin, reserved, reserveSucceeded);
                return false;
            }
        }
        // If invalid, always expect the reservation to fail.
        else
        {
            if (manager.reservePin(pin))
            {
                std::printf("Reservation of pin %u failed: the pin is invalid and should not be able to be reserved!\n", pin);
                return false;
            }
        }
    }
    printf("Pin manager test succeeded!\n\n");
    return true;
}
} // namespace test
