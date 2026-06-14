//! @note Please skip the redundant @file parameter.
/**
 * @file stub.h
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
 */
class Stub final : public Interface
{
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
     * @brief Initialize the ADC stub.
     * 
     * @return True if the ADC was initialized successfully, false otherwise.
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
     * @brief Deinitialize the ADC stub.
     * 
     * @return True if the ADC was deinitialized successfully, false otherwise.
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
     * @brief Check if the ADC stub is initialized.
     * 
     * @return True if initialized and ready, false otherwise.
     */
    bool isInitialized() const noexcept override 
    { 
        return myIsInitialized; 
    }

    /**
     * @brief Read raw digital value from the simulated ADC.
     *
     * @return Simulated raw ADC value.
     */
    std::uint16_t readRaw() const noexcept override 
    { 
        return myRawInput; 
    }

    /**
     * @brief Read the simulated input voltage in Volts.
     * 
     * @return Simulated input voltage in Volts.
     */
    float readVoltage() const noexcept override 
    { 
        //! @note Please avoid magic numbers, use constexpr instead, for instance:
        //!       constexpr float rawMax{4095f};
        //!       constexpr float supplyVoltage{3.3f};
        return (static_cast<float>(myRawInput) / 4095.0f) * 3.3f; 
    }

    /**
     * @brief Simulation of hardware input.
     * 
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
    //! @note Please comment these.
    std::uint16_t myRawInput;
    bool myIsInitialized; 
};
} // namespace driver::adc
