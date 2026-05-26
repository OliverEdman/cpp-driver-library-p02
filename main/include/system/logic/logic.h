
/**
 * @file logic.h
 * @brief Declaration of the logic class.
 */

#pragma once

#include <memory>
#include <atomic>
#include <string>
#include <cstdint>


namespace driver {
    namespace factory { class Interface; }
    namespace gpio { class Interface; }
    namespace serial { class Interface; }
    namespace timer { class Interface; }
    namespace adc { class Interface; }
    namespace tempsensor { class Interface; }
}

namespace system::logic {

/**
 * @class Logic
 * @brief Coordinates system logic by communicating with interfaces.
 * * This class implements the core application logic ()toggling LEDs,
 * and reading sensors etc). 
 */

class Logic final {
public:
    /**
     * @brief Constructor 
     * @param[in] factory Must Reference to an abstract driver factory used to create drivers.
     */
    explicit Logic(driver::factory::Interface& factory) noexcept;

    /**
     * @brief Destructor clean up.
     */
    ~Logic() noexcept = default;

    /**
     * @brief The main execution loop of the system.
     * @param[in] stop An atomic boolean used to safely terminate the execution loop.
     */
    void run(std::atomic<bool>& stop) noexcept;

    // no copy move
    Logic(const Logic&) = delete;
    Logic& operator=(const Logic&) = delete;
    Logic(Logic&&) = delete;
    Logic& operator=(Logic&&) = delete;

private:
    
    // Factory reference 
    driver::factory::Interface& myFactory;

    // System logic owns its drivers through smart pointers
    std::unique_ptr<::driver::serial::Interface> mySerial;
    std::unique_ptr<::driver::gpio::Interface> myLed;
    std::unique_ptr<::driver::timer::Interface> myTimer;
    std::unique_ptr<::driver::adc::Interface> myAdc;
    std::unique_ptr<::driver::tempsensor::Interface> myTempSensor;

    // Internal system state variables

    bool myBlinkActive{false}; // Tracks if the LED timer blink mode is enabled.
    std::uint32_t myPeriodMs{500}; //Current LED blink interval in milliseconds.
};

} // namespace system::logic