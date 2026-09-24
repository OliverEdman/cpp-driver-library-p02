#ifndef GPIO_MOCK_H_
#define GPIO_MOCK_H_

/**
 * @file gpio_mock.h
 * @brief Fake ESP32 GPIO functions used by the tests.
 *
 * This file replaces the real ESP32 GPIO hardware during tests. The GPIO
 * driver calls these functions as if it were connected to an ESP32, but the
 * functions only save values in variables. This allows the tests to check what
 * the driver does without using a real Hardware.
 */

#include "arch/env/test/esp32/types.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef int gpio_num_t;

#define GPIO_MODE_INPUT_OUTPUT 3
#define GPIO_PULLUP_DISABLE 0
#define GPIO_PULLUP_ENABLE 1
#define GPIO_PULLDOWN_DISABLE 0
#define GPIO_INTR_DISABLE 0

    typedef struct
    {
        uint64_t pin_bit_mask;
        int mode;
        int pull_up_en;
        int pull_down_en;
        int intr_type;
    } gpio_config_t;

    inline int gpio_mock_last_pin        = -1;
    inline int gpio_mock_last_level      = 0;
    inline int gpio_mock_level           = 0;
    inline int gpio_mock_set_level_calls = 0;

    /**
     * @brief Gets a pin number from a bit mask.
     *
     * The ESP32 GPIO configuration uses a bit mask instead of receiving the
     * pin number directly. Bit 0 represents pin 0, bit 1 represents pin 1,
     * and so on. The driver sets the bit that belongs to the pin it wants to
     * configure.
     *
     * This function searches for the bit that is set to 1 and converts it back
     * to a pin number. The mock needs this so the tests can see which pin the
     * driver tried to configure. It returns -1 if no bit is set.
     *
     * @return The pin number, or -1 if no bit is set.
     */
    static inline int gpio_mock_pin_from_mask(uint64_t pin_bit_mask)
    {
        int pin = -1;
        for (int i = 0; i < 64; ++i)
        {
            if ((pin_bit_mask & (1ULL << i)) != 0ULL)
            {
                pin = i;
                break;
            }
        }
        return pin;
    }

    /**
     * @brief Starts the mock from its default state.
     *
     * Tests call this before a new check so results from an earlier check do
     * not affect the next test.
     */
    static inline void gpio_mock_reset(void)
    {
        gpio_mock_last_pin        = -1;
        gpio_mock_last_level      = 0;
        gpio_mock_level           = 0;
        gpio_mock_set_level_calls = 0;
    }

    /**
     * @brief Chooses the value returned when the driver reads a GPIO pin.
     *
     * Use 1 for HIGH and 0 for LOW in a test.
     */
    static inline void gpio_mock_set_level_value(int level) { gpio_mock_level = level; }

    /**
     * @brief Returns the number of the last pin used by the driver.
     *
     * @return The last pin number stored by the mock.
     */
    static inline int gpio_mock_get_last_pin(void) { return gpio_mock_last_pin; }

    /**
     * @brief Returns the last value written by the driver.
     *
     * The returned value is normally 1 for HIGH or 0 for LOW.
     *
     * @return The last GPIO value written by the driver.
     */
    static inline int gpio_mock_get_last_level(void) { return gpio_mock_last_level; }

    /**
     * @brief Returns how many times the driver tried to write a GPIO value.
     *
     * This helps a test check that a write happened, or that no write happened.
     *
     * @return The number of calls to gpio_set_level().
     */
    static inline int gpio_mock_get_set_level_calls(void) { return gpio_mock_set_level_calls; }

    /**
     * @brief Pretends to configure a GPIO pin.
     *
     * The function saves the pin number from the configuration.
     *
     * @return ESP_ERR_INVALID_ARG if config is null; otherwise ESP_OK.
     */
    static inline esp_err_t gpio_config(const gpio_config_t* config)
    {
        if (config == nullptr) { return ESP_ERR_INVALID_ARG; }

        gpio_mock_last_pin = gpio_mock_pin_from_mask(config->pin_bit_mask);
        return ESP_OK;
    }

    /**
     * @brief Pretends to reset a GPIO pin.
     *
     *
     * @return ESP_OK after the mock resets the saved pin.
     */
    static inline esp_err_t gpio_reset_pin(gpio_num_t gpio_num)
    {
        (void)gpio_num;
        gpio_mock_last_pin = -1;
        return ESP_OK;
    }

    /**
     * @brief Pretends to write HIGH or LOW to a GPIO pin.
     *
     * The function saves the pin number, the value, and the number of write
     * calls so a test can check them later.
     *
     * @return ESP_OK after the mock stores the written value.
     */
    static inline esp_err_t gpio_set_level(gpio_num_t gpio_num, uint32_t level)
    {
        gpio_mock_last_pin   = static_cast<int>(gpio_num);
        gpio_mock_last_level = static_cast<int>(level);
        gpio_mock_level      = static_cast<int>(level);
        ++gpio_mock_set_level_calls;
        return ESP_OK;
    }

    /**
     * @brief Pretends to read the current value of a GPIO pin.
     *
     * It returns the value stored by gpio_mock_set_level_value() or by the last
     * call to gpio_set_level().
     *
     * @return The current GPIO value stored in the mock.
     */
    static inline int gpio_get_level(gpio_num_t gpio_num)
    {
        (void)gpio_num;
        return gpio_mock_level;
    }

#ifdef __cplusplus
}
#endif

#endif /** GPIO_MOCK_H_ */