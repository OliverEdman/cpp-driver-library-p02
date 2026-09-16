#include "yrgo/test/test.h"

#include "driver/gpio/direction.h"
#include "driver/gpio/esp32s3.h"
#include "arch/env/test/esp32/gpio_mock.h"


/****************************************************************************************
 *                              NOTERING TILL MIG SJÄLV
 * 
 * ESP IDF funktioner använder intar istället för bool där 0 är false och 1 är true
 *
 * level i funktionerna är samma sak som state av typen bool logisk 0 eller 1a
 *
 ****************************************************************************************/

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

TEST(Esp32s3GpioTest, WriteFunction)
{
    // Skapar en variabel för en pinne som vi kan ha som ingående parameter och öka med 1 varje varv så vi testar alla pinnar.
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

        // Rensar ifall mina variabler har ändras. Detta är som en init funktion sätter varaibler till standard värden.
        gpio_mock_reset();

        driver::gpio::Esp32s3 inputPin(testpin, driver::gpio::Direction::Input);

        if (inputPin.isInitialized())
        {
            inputPin.write(true);
            
            // Kontrollerar så att Inget anrop till gpio_set_level ska ha skett eftersom det är en Input
            EXPECT_EQ(gpio_mock_get_set_level_calls(), 0);
        }
    }
}