/**
 * @brief GPIO driver stub.
 */
#pragma once

#include <cstdint>
#include "driver/gpio/interface.h"

namespace driver::gpio
{
/**
 * @brief GPIO driver stub.
 * 
 *        This class is non-copyable and non-movable.
 */
class Stub final : public Interface
{
public:
    /**
     * @brief Constructor.
     */
    Stub() noexcept
        : myState{false}
    {}

    /**
     * @brief Destructor.
     */
    ~Stub() noexcept override = default;

    /**
     * @brief Write GPIO state.
     * 
     * @param[in] state True to enable the GPIO, false otherwise.
     */
    void write(bool state) noexcept override {
        myState = state;
    }

    /**
     * @brief Read GPIO state.
     * 
     * @return True if the GPIO is active/high, false otherwise.
     */
    bool read() const noexcept override {
        return myState;
    }

    /**
     * @brief Toggle the GPIO.
     */
    void toggle() noexcept override {
        myState = !myState;
    }

    Stub(const Stub&)            = delete; // No copy constructor.
    Stub(Stub&&)                 = delete; // No move constructor.
    Stub& operator=(const Stub&) = delete; // No copy assignment.
    Stub& operator=(Stub&&)      = delete; // No move assignment.

private:
    /** Simulated state (true = high, false = low). */
    bool myState;
};
} // namespace driver::gpio
