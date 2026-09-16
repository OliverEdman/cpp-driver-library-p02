#ifndef ESP32_TYPES_H_
#define ESP32_TYPES_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define ESP_OK 0
#define ESP_FAIL -1
#define ESP_ERR_INVALID_ARG -2
#define ESP_ERR_INVALID_ARGUMENT ESP_ERR_INVALID_ARG
#define ESP_ERR_INVALID_STATE -3
#define ESP_ERR_NVS_NO_FREE_PAGES -4
#define ESP_ERR_NVS_NEW_VERSION_FOUND -5

    typedef int esp_err_t;

#define IRAM_ATTR

#ifdef __cplusplus
}
#endif

#endif /** ESP32_TYPES_H_ */
