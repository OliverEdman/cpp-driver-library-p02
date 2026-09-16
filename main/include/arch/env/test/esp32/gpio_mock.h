#ifndef GPIO_MOCK_H_
#define GPIO_MOCK_H_

#include "arch/env/test/esp32/types.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef int gpio_num_t;

#define GPIO_MODE_INPUT 1
#define GPIO_MODE_OUTPUT 2
#define GPIO_MODE_INPUT_OUTPUT 3
#define GPIO_PULLUP_DISABLE 0
#define GPIO_PULLUP_ENABLE 1
#define GPIO_PULLDOWN_DISABLE 0
#define GPIO_PULLDOWN_ENABLE 1
#define GPIO_INTR_DISABLE 0

    typedef struct
    {
        uint64_t pin_bit_mask;
        int mode;
        int pull_up_en;
        int pull_down_en;
        int intr_type;
    } gpio_config_t;

    inline int gpio_mock_last_pin            = -1;
    inline int gpio_mock_last_level          = 0; 
    inline int gpio_mock_level               = 0;
    inline int gpio_mock_set_level_calls     = 0;
    inline int gpio_mock_config_calls        = 0;
    inline esp_err_t gpio_mock_config_result = ESP_OK;

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

    static inline void gpio_mock_reset(void)
    {
        gpio_mock_last_pin        = -1;
        gpio_mock_last_level      = 0;
        gpio_mock_level           = 0;
        gpio_mock_set_level_calls = 0;
        gpio_mock_config_calls    = 0;
        gpio_mock_config_result   = ESP_OK;
    }

    static inline void gpio_mock_set_level_value(int level) { gpio_mock_level = level; }
    static inline void gpio_mock_set_config_result(esp_err_t result) { gpio_mock_config_result = result; }
    
    static inline int gpio_mock_get_last_pin(void) { return gpio_mock_last_pin; }
    static inline int gpio_mock_get_last_level(void) { return gpio_mock_last_level; }
    static inline int gpio_mock_get_set_level_calls(void) { return gpio_mock_set_level_calls; }

    static inline esp_err_t gpio_config(const gpio_config_t* config)
    {
        ++gpio_mock_config_calls;
        if (config == nullptr) { return ESP_ERR_INVALID_ARG; }

        gpio_mock_last_pin = gpio_mock_pin_from_mask(config->pin_bit_mask);
        return gpio_mock_config_result;
    }

    static inline esp_err_t gpio_reset_pin(gpio_num_t gpio_num)
    {
        (void)gpio_num;
        gpio_mock_last_pin = -1;
        return ESP_OK;
    }

    static inline esp_err_t gpio_set_level(gpio_num_t gpio_num, uint32_t level)
    {
        gpio_mock_last_pin   = static_cast<int>(gpio_num);
        gpio_mock_last_level = static_cast<int>(level); 
        gpio_mock_level      = static_cast<int>(level);
        ++gpio_mock_set_level_calls;
        return ESP_OK;
    }

    static inline int gpio_get_level(gpio_num_t gpio_num)
    {
        (void)gpio_num;
        return gpio_mock_level; 
    }

#ifdef __cplusplus
}
#endif

#endif /** GPIO_MOCK_H_ */