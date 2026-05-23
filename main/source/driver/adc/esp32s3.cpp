/**
 * @brief ADC driver for ESP32-S3. 
 */

#include <cstdio>
#include <cstdint>

#include "driver/adc/esp32s3.h"
#include "system/pin_manager/esp32s3.h"

namespace driver::adc 
{
namespace
{
/**
 * @brief Check if given GPIO pin is a valid ADC pin (1-10).
 * 
 * @param[in] pin The GPIO pin to check.
 * 
 * @return True if valid, false otherwise.
 */
bool isAdcPin(const std::uint8_t pin) noexcept 
{
    return (pin >= 1U) && (pin <= 10U);
}

/**
 * @brief Convert from a GPIO pin to the corresponding ADC1 channel.
 * 
 * @param[in] pin GPIO pin number.
 * 
 * @return adc_channel_t corresponding ADC channel.
 * 
 * @example pin = 4
 *          pin - 1 = 3
 *          Result: ADC_CHANNEL_3
 */
adc_channel_t pinToAdc1Channel(const std::uint8_t pin) noexcept
{
    return static_cast<adc_channel_t>(pin - 1U);
}

/** Singleton pin manager instance. */
auto& myPinManager = system::pin_manager::Esp32s3::instance();

} // namespace

/**
 * @brief Constructor.
 * 
 * @param[in] pin The GPIO pin to read analog value from (1-10).
 */
Esp32s3::Esp32s3(std::uint8_t pin) noexcept
    : myState{false}
    , myPin{pin}
    , myChannel{ADC_CHANNEL_0}
    , myHandle{nullptr}
{}

    
/**
* @brief Check if the ADC is initialized.
* 
* @return True if initialized, false otherwise.
*/
bool Esp32s3::isInitialized() const noexcept 
{
    return myState;
}
bool Esp32s3::init() noexcept
{
    // Return false if ADC is already initialized.
    if (myState)
    {
        return false;
    }

    // Return false on invalid ADC pin.
    if (!isAdcPin(myPin))
    {
        return false;
    }

    // Try to book a GPIO pin via the pin manager, return false on failure.
    if (!myPinManager.reservePin(myPin))
    {
        return false;
    }

    // ADC1 only: GPIO1 maps to ADC_CHANNEL_0.
    myChannel = pinToAdc1Channel(myPin);

    // Configure default mode.
    adc_oneshot_unit_init_cfg_t unitConfig{};
    unitConfig.unit_id = ADC_UNIT_1;
    unitConfig.ulp_mode = ADC_ULP_MODE_DISABLE;

    // Create the ESP-IDF ADC unit before configuring the channel.
    // ESP-IDF returns ESP_OK on success.
    if (adc_oneshot_new_unit(&unitConfig, &myHandle) != ESP_OK)
    {
        myPinManager.releasePin(myPin);
        return false;
    }
    adc_oneshot_chan_cfg_t channelConfig = {};
    channelConfig.bitwidth = ADC_BITWIDTH_DEFAULT;
    channelConfig.atten = ADC_ATTEN_DB_12;

    // Release resources on configuration failure.
    if (adc_oneshot_config_channel(myHandle, myChannel, &channelConfig) != ESP_OK)
    {
        adc_oneshot_del_unit(myHandle);
        myHandle = nullptr;
        myPinManager.releasePin(myPin);
        return false;
    }

    myState = true;
    return true;
}

/**
 * @brief Deinitiate ADC
 *
 * @return True if the ADC was deinitialized succesfully, false otherwise.
 *
 */
bool Esp32s3::deinit() noexcept 
{
    // Return false if init() never succeeded.
    if ( !myState ) { return false; }
    
    // Release ESP-IDF ADC unit resources.
    if(adc_oneshot_del_unit(myHandle) != ESP_OK) { return false; }

    myHandle = nullptr;
    myPinManager.releasePin(myPin);

    myState = false;
    return true;
}

std::uint16_t Esp32s3::readRaw() const noexcept
{
    // Check if ADC is initiated, return 0 on failure.
    if (!myState) { return 0U; }

    // Create an int to match ESP-IDF preference.
    int rawValue{0U};

    // Read raw ADC value, return 0 on failure.
    if(adc_oneshot_read(myHandle, myChannel, &rawValue) != ESP_OK)
    {
        return 0U;
    }
    return static_cast<std::uint16_t>(rawValue);
}

float Esp32s3::readVoltage() const noexcept
{
    constexpr float maxRawValue{4095.0F};
    constexpr float supplyVoltage{3.3F};

    // Get raw ADC value (0-4095).
    const auto rawValue = readRaw();

    // Convert raw ADC value to volts.
    return (rawValue / maxRawValue) * supplyVoltage;
}

} // namespace driver::adc 
