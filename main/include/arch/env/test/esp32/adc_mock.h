#ifndef ADC_MOCK_H_
#define ADC_MOCK_H_

#include "arch/env/test/esp32/types.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef void* adc_oneshot_unit_handle_t;
    typedef int adc_channel_t;

#define ADC_UNIT_1 1
#define ADC_CHANNEL_0 0
#define ADC_ULP_MODE_DISABLE 0
#define ADC_BITWIDTH_DEFAULT 12
#define ADC_ATTEN_DB_12 12

    typedef struct
    {
        int unit_id;
        int ulp_mode;
    } adc_oneshot_unit_init_cfg_t;

    typedef struct
    {
        int bitwidth;
        int atten;
    } adc_oneshot_chan_cfg_t;

    static inline esp_err_t adc_oneshot_new_unit(const adc_oneshot_unit_init_cfg_t* init_config,
                                                 adc_oneshot_unit_handle_t* ret_unit)
    {
        static int unit;
        (void)init_config;
        if (ret_unit == nullptr) { return ESP_ERR_INVALID_ARG; }
        *ret_unit = &unit;
        return ESP_OK;
    }

    static inline esp_err_t adc_oneshot_config_channel(adc_oneshot_unit_handle_t handle,
                                                       adc_channel_t channel,
                                                       const adc_oneshot_chan_cfg_t* config)
    {
        (void)handle;
        (void)channel;
        (void)config;
        return ESP_OK;
    }

    static inline esp_err_t adc_oneshot_read(adc_oneshot_unit_handle_t handle,
                                             adc_channel_t channel, int* out_raw)
    {
        (void)handle;
        (void)channel;
        if (out_raw == nullptr) { return ESP_ERR_INVALID_ARG; }
        *out_raw = 0;
        return ESP_OK;
    }

    static inline esp_err_t adc_oneshot_del_unit(adc_oneshot_unit_handle_t handle)
    {
        (void)handle;
        return ESP_OK;
    }

#ifdef __cplusplus
}
#endif

#endif /** ADC_MOCK_H_ */
