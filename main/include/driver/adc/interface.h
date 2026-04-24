/**
 * @brief ADC driver interface
 */
#pragma once 

#include <cstdint>

namespace driver::adc
{
/**
 * @brief ADC driver interface.
 */
class Interface
{
public:    
    /**
     * @brief Destructor.
     */
    virtual ~Interface() noexcept = default;
    
    /**
     * @brief Initiate ADC
     * 
     * @return True if the ADC was initialized successfully, false otherwise.
     */
    virtual bool init() noexcept = 0;

    /**
     * @brief Deinitiate ADC
     * 
     * @return True if the ADC was deinitialized succesfully, false otherwise.
     * 
     */
    virtual bool deinit() noexcept = 0;

    /**
     * @brief Read input from the given pin.
     * 
     * @return Input value.
     */
    virtual std::uint16_t read() const noexcept = 0;
};
} // namespace driver::adc
