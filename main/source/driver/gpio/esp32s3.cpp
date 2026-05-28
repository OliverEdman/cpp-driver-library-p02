/**
 * @brief GPIO driver implementation details for ESP32-S3.
 */
// Standard headers.
#include <cstdint>

// ESP32-specific headers.
#include "driver/gpio.h"

// Local headers.
#include "driver/gpio/direction.h"
#include "driver/gpio/esp32s3.h"
#include "system/pin_manager/esp32s3.h"


namespace driver::gpio
{
// -----------------------------------------------------------------------------

/** Singleton pin manager instance. */
auto& myPinManager = sys::pin_manager::Esp32s3::instance();

// -----------------------------------------------------------------------------
Esp32s3::Esp32s3(std::uint8_t pin, Direction direction) noexcept
    : myPin{pin}
    , myDirection{direction}
    , myInitialized{false}
{
    // Validate and reserve pin.
    if (!myPinManager.reservePin(myPin)) { return; }

    // Create GPIO config.
    // Configure GPIO mode based on direction.
    gpio_config_t config{};
    config.pin_bit_mask = (1ULL << pin);

    // Configure GPIO direction.
    if (direction == Direction::Output)
    {
        config.mode = GPIO_MODE_OUTPUT;
    } else
    {
        config.mode = GPIO_MODE_INPUT;
    }

    // Disable pull-down resistor and interrupts.
    config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    config.intr_type    = GPIO_INTR_DISABLE;

    
    // Enable pull-up resistor if specified.
    const auto pullup = direction == Direction::InputPullup ? GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE;
    config.pull_up_en = pullup;
    const esp_err_t result = gpio_config(&config);

    // Store initialization state.
    myInitialized = (result == ESP_OK);

    // Release pin if initialization failed.
    if (!myInitialized)
    {
        myPinManager.releasePin(myPin);
    }
}

// -----------------------------------------------------------------------------
Esp32s3::~Esp32s3() noexcept 
{
    // Reset the gpio pin and pin manager.
    gpio_reset_pin(myPin);
    myPinManager.releasePin(myPin);
}

// -----------------------------------------------------------------------------
void Esp32s3::write(bool state) noexcept
{
    // Check data direction, ignore if input.
    if (Direction::Output != myDirection) { return; }
    gpio_set_level(myPin, state);
}

// -----------------------------------------------------------------------------
bool Esp32s3::read() const noexcept
{
    // Read state, cast to bool (1 => true, 0 => false).
    return static_cast<bool>(gpio_get_level(myPin));
}

// -----------------------------------------------------------------------------
void Esp32s3::toggle() noexcept
{
    // Read the pin, toggle the state.
    const auto state = read();
    write(!state);
}

// -----------------------------------------------------------------------------
bool Esp32s3::isInitialized() const noexcept
{
    return myInitialized;
}
} // namespace driver::gpio