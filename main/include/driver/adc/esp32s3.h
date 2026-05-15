/**
 * @brief ADC driver for ESP32-S3. 
 */
#pragma once

#include "driver/adc/interface.h"

namespace driver::adc 
{


class Esp32s3 final : public Interface
{

        /**
         * @note 
         * GPIO 1-10    SAR ADC1
         * GPIO 11-20   SAR ADC2
         */
public:    
    /**
     * @brief Constructor.
     * 
     * @param[in] pin The pin to read analog value from (0-7).
     */
    explicit Esp32s3(std::uint8_t pin) noexcept
        
    {}
    /**
     * @brief Destructor.
     */
     ~Esp32s3() noexcept override = default;
     
    /**
     * @brief Check if the ADC is initialized.
     * 
     * @return True if initialized, false otherwise.
     */
     bool isInitialized() const noexcept override;

     /**
      * @brief Initiate ADC
      *
      * @return True if the ADC was initialized successfully, false otherwise.
      */
     bool init() noexcept override;

     /**
      * @brief Deinitiate ADC
      *
      * @return True if the ADC was deinitialized succesfully, false otherwise.
      *
      */
     bool deinit() noexcept override;

    /**
    * @brief Read input from the given pin.
    *
    * @return Input value.
    */
    std::uint16_t read() const noexcept override;
    
    
    Esp32s3(const Esp32s3&)            = delete; // No copy constructor.
    Esp32s3(Esp32s3&&)                 = delete; // No move constructor.
    Esp32s3& operator=(const Esp32s3&) = delete; // No copy assignment.
    Esp32s3& operator=(Esp32s3&&)      = delete; // No move assignment.
private:
    /** ADC state. */
    bool myState;
    /** Target ADC pin. */
    std::uint8_t myPin;
    /** ADC channel (1,2) */
    std::uint8_t myChannel;

};
} // namespace driver::adc 
