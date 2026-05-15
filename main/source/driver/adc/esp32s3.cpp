/**
 * @brief ADC driver for ESP32-S3. 
 */
#pragma once

#include "driver/adc/esp32s3.h"

namespace driver::adc 
{

    /**
     * @brief Constructor.
     * 
     * @param[in] pin The pin to read analog value from (0-7).
     */
    explicit Esp32s3(std::uint8_t pin) noexcept
    {
        
    }

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
     bool std::uint16_t read() const noexcept override;
    


} // namespace driver::adc 
