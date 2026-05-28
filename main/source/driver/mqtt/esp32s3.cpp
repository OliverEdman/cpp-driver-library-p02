/**
 * @brief MQTT driver implementation details for ESP32-S3.
 */

// Standard headers.
#include <cstdint>
#include <cstring>

// Local headers.
#include "driver/mqtt/esp32s3.h"

extern "C" 
{
#include "mqtt_client.h"
} // extern "C"


namespace driver::mqtt
{
// -----------------------------------------------------------------------------
Esp32s3::Esp32s3(const char* brokerUri,
            const char* clientId) noexcept
    : myHandle{nullptr}
    , myBrokerUri{brokerUri}
    , myClientId{clientId}
    , myConnected{false}
{}

// -----------------------------------------------------------------------------
Esp32s3::~Esp32s3() noexcept
{
    disconnect();
}

// -----------------------------------------------------------------------------
bool Esp32s3::connect() noexcept
{
    const esp_mqtt_client_config_t config{
        .broker = {.address.uri = myBrokerUri},
        .credentials = {.client_id = myClientId},
    };

    // Initialize MQTT client, return false on failure.
    myHandle = esp_mqtt_client_init(&config);
    if (nullptr == myHandle) { return false; }

    esp_mqtt_client_register_event(
    myHandle,
    MQTT_EVENT_ANY,
    &Esp32s3::mqttEventHandler,
    this
    );

    // Start MQTT client.
    myConnected = ESP_OK == esp_mqtt_client_start(myHandle);

    // Return true if connected.
    return myConnected;
}

// -----------------------------------------------------------------------------
void Esp32s3::disconnect() noexcept
{
    // Disconnect only if the handle is initialized.
    if (nullptr != myHandle)
    {
        esp_mqtt_client_stop(myHandle);
        esp_mqtt_client_disconnect(myHandle);
        esp_mqtt_client_destroy(myHandle);
        myHandle = nullptr;
    }
    myConnected = false;
}

// -----------------------------------------------------------------------------
bool Esp32s3::isConnected() const noexcept
{
    return myConnected;
}

// -----------------------------------------------------------------------------
bool Esp32s3::publish(const char* topic, const char* payload) noexcept
{
    // Kolla att topic och payload inte är null, return annars false.
    if ((nullptr == topic) || (nullptr == payload))
    {
        return false;
    }

    // Kolla att vi är connected, returna annars false.
    if (!myConnected)
    {
        return false;
    }

    const auto len = static_cast<int>(std::strlen(payload));
    constexpr int qos{1U};

    // Publish to broker, return true if a message ID was returned.
    return 0 <= esp_mqtt_client_publish(myHandle, topic, payload, len, qos, 0);
}

// -----------------------------------------------------------------------------
bool Esp32s3::subscribe(const char* topic) noexcept
{
    if ((nullptr == myHandle) || (!myConnected) || (nullptr == topic))
    {
        return false;
    }

    constexpr int qos{1};
    const auto result = esp_mqtt_client_subscribe(myHandle, topic, qos);
    return 0 <= result;
}

// -----------------------------------------------------------------------------
void Esp32s3::loop() noexcept
{

}

// -----------------------------------------------------------------------------
void Esp32s3::mqttEventHandler(void* handler_args,
                               esp_event_base_t base,
                               int32_t event_id,
                               void* event_data)
{
    (void)base;
    (void)event_data;

    // Recover class instance from callback context.
    auto* self = static_cast<Esp32s3*>(handler_args);

    switch (event_id)
    {
        case MQTT_EVENT_CONNECTED:
        {
            self->myConnected = true;
            break;
        }

        case MQTT_EVENT_DISCONNECTED:
        {
            self->myConnected = false;
            break;
        }

        default:
        {
            break;
        }
    }
}

// -----------------------------------------------------------------------------
} // namespace driver::mqtt