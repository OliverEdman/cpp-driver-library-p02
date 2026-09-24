#include "yrgo/test/test.h"

#include "driver/adc/esp32s3.h"
#include "system/pin_manager/esp32s3.h"
#include "arch/env/test/esp32/adc_mock.h"


namespace {

/** Count of pins to test (loop tests 0-10) */  
constexpr std::uint8_t pinCount{11U};

/** Max value of the ADC (12 bit). */
constexpr float maxRawValue{4095.0F};

/** Supply voltage in Volt. */
constexpr float supplyVoltage{3.3F};

// Singleton pin manager instance.
auto& myPinManager = sys::pin_manager::Esp32s3::instance();

/** Helper to get ADC pins (1-10). */
bool isAdcPin(const std::uint8_t pin) noexcept
{
    return (pin >= 1U) && (pin <= 10U);
}

/** Helper to compute expected voltage (voltage = raw / 4095 * 3.3). */
float computeInputVoltage(const std::uint16_t rawValue) noexcept
{
    return (rawValue / maxRawValue) * supplyVoltage;
}

} // namespace


/**
 *  Test ADC initialization routine.
 * 
 *  @note adc_mock_reset() resets the mock before every test.
 */
TEST(Esp32s3AdcTest, Initialization)
{
    adc_mock_reset();

    // Test valid pins.
    for (std::uint8_t i{}; i < pinCount; ++i)
    {
        // Pin could be a generally valid GPIO pin, however it
        // could also be an invalid ADC pin at the same time.
        const auto pinValid = myPinManager.isPinValid(i) && isAdcPin(i);
        driver::adc::Esp32s3 myAdc(i);

        if (pinValid)
        {
            EXPECT_TRUE(myAdc.init());
            EXPECT_TRUE(myAdc.isInitialized());
            EXPECT_TRUE(myAdc.deinit());
            EXPECT_FALSE(myAdc.isInitialized());
        }
        else
        {
            EXPECT_FALSE(myAdc.init());
            EXPECT_FALSE(myAdc.isInitialized());
        }
    }

}

/**
 *  Test raw voltage read functionality.
 */
TEST(Esp32s3AdcTest, Read)
{
    adc_mock_reset();
    driver::adc::Esp32s3 myAdc(3U);

    EXPECT_TRUE(myAdc.init());
    adc_mock_set_raw_value(2048);

    EXPECT_EQ(myAdc.readRaw(), 2048U);
    EXPECT_TRUE(myAdc.deinit());
}

/**
 *  Test raw voltage read functionality.
 */
TEST(Esp32s3AdcTest, ReadVoltage)
{
    adc_mock_reset();
    driver::adc::Esp32s3 myAdc(3U);

    EXPECT_TRUE(myAdc.init());
    adc_mock_set_raw_value(4095);

    EXPECT_NEAR(myAdc.readVoltage(), computeInputVoltage(4095U), 0.01F);
    EXPECT_TRUE(myAdc.deinit());
}

/**
 *  Test raw voltage read functionality.
 *  Expect read function to fail and return 0.
 */
TEST(Esp32s3AdcTest, ReadFailure)
{
    adc_mock_reset();
    driver::adc::Esp32s3 myAdc(3U);

    EXPECT_TRUE(myAdc.init());
    adc_mock_set_raw_value(2048);
    adc_mock_set_read_result(ESP_FAIL);

    EXPECT_EQ(myAdc.readRaw(), 0U);
    EXPECT_TRUE(myAdc.deinit());
}

/**
 * Test ADC initialization routine.
 * Expect initialization to fail.
 */
TEST(Esp32s3AdcTest, InitNewUnitFailure)
{
    adc_mock_reset();
    adc_mock_set_new_unit_result(ESP_FAIL);
    driver::adc::Esp32s3 myAdc(3U);

    EXPECT_FALSE(myAdc.init());
    EXPECT_FALSE(myAdc.isInitialized());
}

/**
 * Test ADC config channel.
 * Expect initialization to fail.
 */
TEST(Esp32s3AdcTest, InitConfigChannelFailure)
{
    adc_mock_reset();
    adc_mock_set_config_channel_result(ESP_FAIL);
    driver::adc::Esp32s3 myAdc(3U);

    EXPECT_FALSE(myAdc.init());
    EXPECT_FALSE(myAdc.isInitialized());
}
