/**
 * @brief ADC driver stub for simulation.
 */
#pragma once 

#include <cstdint>
#include <cstdio>
#include "driver/adc/interface.h"


namespace driver::adc
{
/**
 * @brief ADC stub implementation.
 * Used to test without hardware.
 */
class Stub final : public Interface
{

private :
static constexpr float MaxRawValue{4095.0f};
static constexpr float SupplyVoltage{3.3f};

public:
    /**
     * @brief Constructor.
     */
    Stub() noexcept
        : myRawInput{0U}
        , myIsInitialized{false}
    {}

    /**
     * @brief Destructor.
     */
    ~Stub() noexcept override = default;

    /**
     * @brief Initiate ADC 
     * @return True if success.
     */
    bool init() noexcept override 
    {
        // Return false if the ADC is already initialized.
        if (myIsInitialized) { return false; }
        myIsInitialized = true;
        std::printf("ADC initialized!\n");
        return true;
    }

    /**
     * @brief Deinitiate ADC
     * @return True if success.
     */
    bool deinit() noexcept override 
    {
        // Return false if the ADC is already uninitialized.
        if (!myIsInitialized) { return false; }
        myIsInitialized = false;
        std::printf("ADC deinitialized!\n");
        return true;
    }

    /**
     * @brief Check if initialized.
     */
    bool isInitialized() const noexcept override 
    { 
        return myIsInitialized; 
    }

    /**
     * @brief Returns the simulated raw value (0-4095).
     */
    std::uint16_t readRaw() const noexcept override 
    { 
        return myRawInput; 
    }

    /**
     * @brief Returns the simulated voltage.
     * Formula: (raw / 4095.0) * 3.3V
     */
    float readVoltage() const noexcept override 
    { 
        return (static_cast<float>(myRawInput) / MaxRawValue) * SupplyVoltage; 
    }

    /**
     * @brief Simulation of hardware input.
     * @param[in] input Raw value to simulate.
     */
    void simulateInput(const std::uint16_t input) noexcept 
    { 
        myRawInput = input; 
    }

    // Delete copy/move constructors
    Stub(const Stub&)            = delete;
    Stub(Stub&&)                 = delete;
    Stub& operator=(const Stub&) = delete;
    Stub& operator=(Stub&&)      = delete;

private:
    std::uint16_t myRawInput;
    bool          myIsInitialized; 
};

} // namespace driver::adc
