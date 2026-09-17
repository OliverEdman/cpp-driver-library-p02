#include "yrgo/test/test.h"

#include "driver/gpio/direction.h"
#include "driver/gpio/esp32s3.h"
#include "arch/env/test/esp32/gpio_mock.h"


/**
 * @brief Checks that an input pin reads the current logic level from the GPIO mock.
 *
 * The test first sets the mocked pin level to HIGH and expects `read()` to return
 * true. It then sets the level to LOW and expects `read()` to return false.
 * This verifies that the GPIO driver converts the ESP-IDF-style integer level
 * (0 or 1) into the driver's boolean result correctly.
 */
TEST(Esp32s3GpioTest, ReadFunction)
{
    gpio_mock_reset();

    driver::gpio::Esp32s3 pin(0, driver::gpio::Direction::Input);

    if (pin.isInitialized())
    {
        gpio_mock_set_level_value(1);
        EXPECT_TRUE(pin.read());

    
        gpio_mock_set_level_value(0);
        EXPECT_FALSE(pin.read());
    }
}

/**
 * @brief Checks that the GPIO driver writes the correct value to output pins.
 *
 * The test also checks that writing to an input pin does not change the GPIO
 * State. It repeats these checks for pins 0 through 15.
 */
TEST(Esp32s3GpioTest, WriteFunction)
{
    // Increase the pin number on every iteration so pins 0 through 15 are tested.
    for (std::uint8_t testpin = 0; testpin <= 15; ++testpin)
    {
        gpio_mock_reset();

        driver::gpio::Esp32s3 outputPin(testpin, driver::gpio::Direction::Output);

        if (outputPin.isInitialized()) 
        {
            outputPin.write(true);
            EXPECT_TRUE(outputPin.read());
            EXPECT_EQ(gpio_mock_get_last_level(), 1); 

            outputPin.write(false); 
            EXPECT_EQ(gpio_mock_get_last_pin(), testpin);
            EXPECT_EQ(gpio_mock_get_last_level(), 0);
        }

        // Reset the mock before testing the next pin direction.
        gpio_mock_reset();

        driver::gpio::Esp32s3 inputPin(testpin, driver::gpio::Direction::Input);

        if (inputPin.isInitialized())
        {
            inputPin.write(true);
            
            // An input pin should NOT call gpio_set_level when write() is used.
            EXPECT_EQ(gpio_mock_get_set_level_calls(), 0);
        }
    }
}