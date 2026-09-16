#ifndef WIFI_MOCK_H_
#define WIFI_MOCK_H_

#include "arch/env/test/esp32/types.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef const char* esp_event_base_t;
typedef void* esp_event_handler_instance_t;
typedef void (*esp_event_handler_t)(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data);

typedef struct esp_netif_t
{
    int dummy;
} esp_netif_t;

#define ESP_EVENT_ANY_ID (-1)
static const char wifi_event_base[] = "WIFI_EVENT";
static const char ip_event_base[] = "IP_EVENT";
#define WIFI_EVENT wifi_event_base
#define IP_EVENT ip_event_base
#define WIFI_EVENT_STA_START 1
#define WIFI_EVENT_STA_DISCONNECTED 2
#define IP_EVENT_STA_GOT_IP 3

typedef struct
{
    int dummy;
} wifi_init_config_t;

#define WIFI_INIT_CONFIG_DEFAULT() wifi_init_config_t {}

#define WIFI_MODE_STA 1
#define WIFI_IF_STA 0

typedef struct
{
    uint8_t ssid[32];
    uint8_t password[64];
} wifi_sta_config_t;

typedef struct
{
    wifi_sta_config_t sta;
} wifi_config_t;

static inline esp_err_t nvs_flash_init(void) { return ESP_OK; }
static inline esp_err_t nvs_flash_erase(void) { return ESP_OK; }
static inline esp_err_t esp_netif_init(void) { return ESP_OK; }
static inline esp_err_t esp_event_loop_create_default(void) { return ESP_OK; }

static inline esp_netif_t* esp_netif_create_default_wifi_sta(void)
{
    static esp_netif_t netif;
    return &netif;
}

static inline void esp_netif_destroy_default_wifi(esp_netif_t* netif)
{
    (void)netif;
}

static inline esp_err_t esp_wifi_init(const wifi_init_config_t* config)
{
    (void)config;
    return ESP_OK;
}

static inline esp_err_t esp_wifi_deinit(void) { return ESP_OK; }
static inline esp_err_t esp_wifi_set_mode(int mode)
{
    (void)mode;
    return ESP_OK;
}

static inline esp_err_t esp_wifi_set_config(int interface, wifi_config_t* config)
{
    (void)interface;
    (void)config;
    return ESP_OK;
}

static inline esp_err_t esp_wifi_start(void) { return ESP_OK; }
static inline esp_err_t esp_wifi_stop(void) { return ESP_OK; }
static inline esp_err_t esp_wifi_connect(void) { return ESP_OK; }
static inline esp_err_t esp_wifi_disconnect(void) { return ESP_OK; }

static inline esp_err_t esp_event_handler_instance_register(
    esp_event_base_t event_base,
    int32_t event_id,
    esp_event_handler_t event_handler,
    void* event_handler_arg,
    esp_event_handler_instance_t* instance)
{
    (void)event_base;
    (void)event_id;
    (void)event_handler;
    (void)event_handler_arg;
    if (instance != nullptr) { *instance = reinterpret_cast<void*>(1); }
    return ESP_OK;
}

static inline esp_err_t esp_event_handler_instance_unregister(
    esp_event_base_t event_base,
    int32_t event_id,
    esp_event_handler_instance_t instance)
{
    (void)event_base;
    (void)event_id;
    (void)instance;
    return ESP_OK;
}

#ifdef __cplusplus
}
#endif

#endif /** WIFI_MOCK_H_ */
