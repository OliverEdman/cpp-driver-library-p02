#include <cstdint>
#include <cstring>

#include "driver/mqtt/esp32s3.h"

extern "C" 
{
#include "mqtt_client.h"
} // extern "C"

namespace
{
void copyMqttField(char* dst, std::uint16_t dstSize, const char* src, int srcLen) noexcept
{
    if ((dst == nullptr) || (dstSize == 0U)) { return; }

    std::uint16_t count{0U};

    if ((src != nullptr) && (srcLen > 0))
    {
        const auto maxCopy = static_cast<std::uint16_t>(dstSize - 1U);
        const auto wanted = static_cast<std::uint16_t>(
            (srcLen < static_cast<int>(maxCopy)) ? srcLen : static_cast<int>(maxCopy)
        );

        while (count < wanted)
        {
            dst[count] = src[count];
            ++count;
        }
    }

    dst[count] = '\0';
}
}

namespace driver::mqtt
{
// -----------------------------------------------------------------------------
Esp32s3::Esp32s3(const char* brokerUri,
            const char* clientId) noexcept
    : myHandle{nullptr}
    , myBrokerUri{brokerUri}
    , myClientId{clientId}
    , myConnected{false}
    , myLastTopic{}
    , myLastPayload{}
    , myMessageAvailable{false}
{}

// -----------------------------------------------------------------------------
Esp32s3::~Esp32s3() noexcept
{
    disconnect();
}

// -----------------------------------------------------------------------------
bool Esp32s3::connect() noexcept
{
    if (myConnected) { return true; }
    if (myHandle != nullptr) { return true; }

    // Configure brokerUri and clientId.
    const esp_mqtt_client_config_t config{
        .broker = {.address.uri = myBrokerUri},
        .credentials = {.client_id = myClientId},
    };

    // Initialize MQTT client, return false on failure.
    myHandle = esp_mqtt_client_init(&config);
    if (nullptr == myHandle) { return false; }

    // Register MQTT event callback handler.
    if (esp_mqtt_client_register_event(myHandle,
                                       MQTT_EVENT_ANY,
                                       &Esp32s3::mqttEventHandler,
                                       this)
        != ESP_OK)
    {
        esp_mqtt_client_destroy(myHandle);
        myHandle = nullptr;
        return false;
    }

    // Start MQTT client.
    if (esp_mqtt_client_start(myHandle) != ESP_OK)
    {
        esp_mqtt_client_destroy(myHandle);
        myHandle = nullptr;
        return false;
    }

    // The actual broker connection is reported asynchronously by MQTT_EVENT_CONNECTED.
    return true;
}

// -----------------------------------------------------------------------------
void Esp32s3::disconnect() noexcept
{
    // Disconnect only if the handle is initialized.
    if (nullptr != myHandle)
    {
        esp_mqtt_client_stop(myHandle);
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
    // Check that topic and payload is nit null, false otherwise
    if ((nullptr == topic) || (nullptr == payload))
    {
        return false;
    }

    // Check to see if connected, false otherwise.
    if (!myConnected)
    {
        return false;
    }

    const auto len = static_cast<int>(std::strlen(payload));
    constexpr int qos{1};

    // Publish to broker, return true if a message ID was returned.
    return 0 <= esp_mqtt_client_publish(myHandle, topic, payload, len, qos, 0);
}

// -----------------------------------------------------------------------------
bool Esp32s3::subscribe(const char* topic) noexcept
{
    // Check to see if myHandle and topic is not null, and myConnected is true, false otherwise
    if ((nullptr == myHandle) || (!myConnected) || (nullptr == topic))
    {
        return false;
    }

    constexpr int qos{1};
    const auto result = esp_mqtt_client_subscribe(myHandle, topic, qos);
    return 0 <= result;
}

// -----------------------------------------------------------------------------
void Esp32s3::loop() noexcept{}

// -----------------------------------------------------------------------------
void Esp32s3::mqttEventHandler(void* handler_args,
                               esp_event_base_t base,
                               int32_t event_id,
                               void* event_data)
{
    (void)base;


    // Recover class instance from callback context.
    if (nullptr == handler_args) { return; }
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
        case MQTT_EVENT_DATA:
        {
            const auto* event = static_cast<esp_mqtt_event_handle_t>(event_data);
            if ( nullptr == event) { break; }

            copyMqttField(self->myLastTopic, topicBufSize, event->topic, event->topic_len);
            copyMqttField(self->myLastPayload, payloadBufSize, event->data, event->data_len);

            self->myMessageAvailable = true;
            break;
        }


        default:
        {
            break;
        }
    }
}

bool Esp32s3::readMessage(char* topic,
                         std::uint16_t topicMaxLen,
                         char* payload,
                         std::uint16_t payloadMaxLen ) noexcept {

    if (!myMessageAvailable) { return false; }
    if ((topic == nullptr) || (payload == nullptr)) { return false; }
    if ((topicMaxLen == 0U) || (payloadMaxLen == 0U)) { return false; }

    copyMqttField(topic, topicMaxLen, myLastTopic, static_cast<int>(std::strlen(myLastTopic)));
    copyMqttField(payload, payloadMaxLen, myLastPayload, static_cast<int>(std::strlen(myLastPayload)));

    myMessageAvailable = false;
    return true;

 }

// -----------------------------------------------------------------------------
} // namespace driver::mqtt
