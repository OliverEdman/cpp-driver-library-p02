#ifndef MQTT_MOCK_H_
#define MQTT_MOCK_H_

#include "arch/env/test/esp32/types.h"
#include "arch/env/test/esp32/wifi_mock.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef void* esp_mqtt_client_handle_t;

typedef struct
{
    const char* uri;
} esp_mqtt_broker_address_t;

typedef struct
{
    esp_mqtt_broker_address_t address;
} esp_mqtt_broker_t;

typedef struct
{
    const char* client_id;
} esp_mqtt_credentials_t;

typedef struct
{
    esp_mqtt_broker_t broker;
    esp_mqtt_credentials_t credentials;
} esp_mqtt_client_config_t;

typedef struct
{
    const char* topic;
    int topic_len;
    const char* data;
    int data_len;
} esp_mqtt_event_t;

typedef esp_mqtt_event_t* esp_mqtt_event_handle_t;
typedef void (*esp_mqtt_event_cb_t)(void* handler_args, esp_event_base_t base,
                                    int32_t event_id, void* event_data);

#define MQTT_EVENT_ANY (-1)
#define MQTT_EVENT_CONNECTED 1
#define MQTT_EVENT_DISCONNECTED 2
#define MQTT_EVENT_DATA 3

static inline esp_mqtt_client_handle_t esp_mqtt_client_init(
    const esp_mqtt_client_config_t* config)
{
    static int client;
    (void)config;
    return &client;
}

static inline esp_err_t esp_mqtt_client_register_event(esp_mqtt_client_handle_t client,
                                                       int32_t event_id,
                                                       esp_mqtt_event_cb_t event_handler,
                                                       void* event_handler_arg)
{
    (void)client;
    (void)event_id;
    (void)event_handler;
    (void)event_handler_arg;
    return ESP_OK;
}

static inline esp_err_t esp_mqtt_client_start(esp_mqtt_client_handle_t client)
{
    (void)client;
    return ESP_OK;
}

static inline esp_err_t esp_mqtt_client_stop(esp_mqtt_client_handle_t client)
{
    (void)client;
    return ESP_OK;
}

static inline esp_err_t esp_mqtt_client_destroy(esp_mqtt_client_handle_t client)
{
    (void)client;
    return ESP_OK;
}

static inline int esp_mqtt_client_publish(esp_mqtt_client_handle_t client,
                                          const char* topic,
                                          const char* data,
                                          int len,
                                          int qos,
                                          int retain)
{
    (void)client;
    (void)topic;
    (void)data;
    (void)len;
    (void)qos;
    (void)retain;
    return 1;
}

static inline int esp_mqtt_client_subscribe(esp_mqtt_client_handle_t client,
                                            const char* topic,
                                            int qos)
{
    (void)client;
    (void)topic;
    (void)qos;
    return 1;
}

#ifdef __cplusplus
}
#endif

#endif /** MQTT_MOCK_H_ */
