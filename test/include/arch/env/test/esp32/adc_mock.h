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

    inline int adc_mock_raw_value                   = 0;
    inline esp_err_t adc_mock_new_unit_result       = ESP_OK;
    inline esp_err_t adc_mock_config_channel_result = ESP_OK;
    inline esp_err_t adc_mock_read_result           = ESP_OK;
    inline esp_err_t adc_mock_del_unit_result       = ESP_OK;

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

    static inline void adc_mock_reset(void)
    {
        adc_mock_raw_value             = 0;
        adc_mock_new_unit_result       = ESP_OK;
        adc_mock_config_channel_result = ESP_OK;
        adc_mock_read_result           = ESP_OK;
        adc_mock_del_unit_result       = ESP_OK;
    }

    static inline void adc_mock_set_raw_value(int value) { adc_mock_raw_value = value; }

    static inline int adc_mock_get_raw_value(void) { return adc_mock_raw_value; }

    static inline void adc_mock_set_new_unit_result(esp_err_t result)
    {
        adc_mock_new_unit_result = result;
    }

    static inline void adc_mock_set_config_channel_result(esp_err_t result)
    {
        adc_mock_config_channel_result = result;
    }

    static inline void adc_mock_set_read_result(esp_err_t result) { adc_mock_read_result = result; }

    static inline void adc_mock_set_del_unit_result(esp_err_t result)
    {
        adc_mock_del_unit_result = result;
    }

    static inline esp_err_t adc_oneshot_new_unit(const adc_oneshot_unit_init_cfg_t* init_config,
                                                 adc_oneshot_unit_handle_t* ret_unit)
    {
        static int unit;
        (void)init_config;
        if (ret_unit == nullptr) { return ESP_ERR_INVALID_ARG; }
        if (adc_mock_new_unit_result != ESP_OK) { return adc_mock_new_unit_result; }
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
        if (adc_mock_config_channel_result != ESP_OK) { return adc_mock_config_channel_result; }
        return ESP_OK;
    }

    static inline esp_err_t adc_oneshot_read(adc_oneshot_unit_handle_t handle,
                                             adc_channel_t channel, int* out_raw)
    {
        (void)handle;
        (void)channel;
        if (out_raw == nullptr) { return ESP_ERR_INVALID_ARG; }
        if (adc_mock_read_result != ESP_OK) { return adc_mock_read_result; }
        *out_raw = adc_mock_raw_value;
        return ESP_OK;
    }

    static inline esp_err_t adc_oneshot_del_unit(adc_oneshot_unit_handle_t handle)
    {
        (void)handle;
        if (adc_mock_del_unit_result != ESP_OK) { return adc_mock_del_unit_result; }
        return ESP_OK;
    }

#ifdef __cplusplus
}
#endif

#endif /** ADC_MOCK_H_ */
