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

    static inline esp_err_t gpio_config(const gpio_config_t* config)
    {
        return (config == nullptr) ? ESP_ERR_INVALID_ARG : ESP_OK;
    }

    static inline esp_err_t gpio_reset_pin(gpio_num_t gpio_num)
    {
        (void)gpio_num;
        return ESP_OK;
    }

    static inline esp_err_t gpio_set_level(gpio_num_t gpio_num, uint32_t level)
    {
        (void)gpio_num;
        (void)level;
        return ESP_OK;
    }

    static inline int gpio_get_level(gpio_num_t gpio_num)
    {
        (void)gpio_num;
        return 0;
    }

#ifdef __cplusplus
}
#endif

#endif /** GPIO_MOCK_H_ */
