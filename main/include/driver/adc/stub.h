/**
 * @brief ADC driver interface
 */
#pragma once 

#include <cstdint>

#include "driver/adc/interface.h"

namespace driver::adc
{
/**
 * @brief ADC driver interface
 */
class Stub final : public Interface
{
public:
    /**
     * @brief Constructor.
     */
    Stub() noexcept
        : myInput{0U}
        , myInitialized(false)
    {}

    /**
     * @brief Destructor.
     */
    ~Stub() noexcept override = default;

    /**
     * @brief Initiate ADC 
     * 
     * 
     */
    bool init() noexcept override 
    {
        // Return false if the ADC is already initialized.
        if (myInitialized) { return false; }
        myInitialized = true;
        std::printf("ADC initialized!");
        return true;
    }

    /**
     * @brief Deinitiate ADC
     * 
     */
    bool deinit() noexcept override 
    {
        // Return false if the ADC is already uninitialized.
        if (!myInitialized) { return false; }
        myInitialized = false;
        std::printf("ADC initialized!");
        return true;
    }

    /**
     * @brief Get the analog value (0 - 4095) from the given pin.
     * 
     * @return Analog value.
     */
    std::uint16_t read() const noexcept override { return myInput; }

    /**
     * @brief Simulate analog input.
     * 
     * @param[in] input Input value.
     */
    void simulateInput(const std::uint16_t input) noexcept { myInput = input; }

    Stub(const Stub&)            = delete; // No copy constructor.
    Stub(Stub&&)                 = delete; // No move constructor.
    Stub& operator=(const Stub&) = delete; // No copy assignment.
    Stub& operator=(Stub&&)      = delete; // No move assignment.

private:
    /** Simulated input. */
    std::uint16_t myInput;
    std::uint8_t myInitialized;
};
} // namespace driver::adc
