/**
 * @brief MQTT driver for the ESP32-S3.
 */
#pragma once

#include <cstdint>

/**
 * @brief Include ESP-IDF MQTT C API with C linkage.
 */
extern "C"
{
#include "mqtt_client.h"
} // extern "C"

#include "driver/mqtt/interface.h"

namespace driver::mqtt
{
/**
 * @brief MQTT driver implementation for ESP32-S3.
 * 
 *        This class uses the built in ESP-IDF functions to talk to an MQTT broker over the network.
 *        It is explicitly non-copyable and non-movable
 */
class Esp32s3 final : public Interface
{
public:
    /**
     * @brief Constructor for the MQTT driver.
     * * @param[in] brokerUri The URI of the MQTT broker.
     * @param[in] clientId  The unique client identifier for this connection.
     */
    explicit Esp32s3(const char* brokerUri, const char* clientId) noexcept;

    /**
     * @brief Destructor.
     */
    ~Esp32s3() noexcept override;

    /**
     * @brief Connect to the MQTT broker.
     *
     * @return True if connection succeeded, false otherwise.
     */
    bool connect() noexcept override;

    /**
     * @brief Disconnect from the MQTT broker.
     */
    void disconnect() noexcept override;

    /**
     * @brief Check the current connection state.
     *
     * @return True if currently connected to the broker, false otherwise.
     */
    bool isConnected() const noexcept override;

    /**
     * @brief Publish MQTT message.
     *
     * @param[in] topic MQTT topic.
     * @param[in] payload Message payload.
     *
     * @return True if the message was successfully published, false otherwise.
     */
    bool publish(const char* topic, const char* payload) noexcept override;

    /**
     * @brief Subscribe to a specific MQTT topic.
     *
     * @param[in] topic MQTT topic.
     *
     * @return True if subscription succeeded, false otherwise.
     */
    bool subscribe(const char* topic) noexcept override;

   /**
     * @brief Process MQTT events and incoming messages.
     *        
     *        Should be called periodically from the main loop/task.
     */
    void loop() noexcept override;

     /**
     * @brief Read an incoming MQTT message from the buffer.
     *
     * @param[in]  topic          Pointer to the buffer where the topic string will be stored.
     * @param[in]  topicMaxLen    Maximum size of the topic buffer in bytes.
     * @param[in]  payload        Pointer to the buffer where the message payload will be stored.
     * @param[in]  payloadMaxLen  Maximum size of the payload buffer in bytes.
     *
     * @return True if a message was successfully read, false otherwise.
     */
    bool readMessage(char* topic, std::uint16_t topicMaxLen, char* payload, std::uint16_t payloadMaxLen) noexcept override;

    // Delete copy/move constructors and operators.
    Esp32s3(const Esp32s3&)            = delete;
    Esp32s3(Esp32s3&&)                 = delete;
    Esp32s3& operator=(const Esp32s3&) = delete;
    Esp32s3& operator=(Esp32s3&&)      = delete;

private:
     /**
     * @brief Static MQTT event callback handler dispatched by the ESP-IDF framework.
     * @param[in] handler_args User arguments.
     * @param[in] base The event base.
     * @param[in] event_id The specific event ID.
     * @param[in] event_data Pointer to the raw event data structure.
     */ 
 static void mqttEventHandler(void* handler_args, esp_event_base_t base,
                                 int32_t event_id, void* event_data);

    /** ESP-IDF MQTT client handle. */
    esp_mqtt_client_handle_t myHandle;

    /** MQTT broker URI. */
    const char* myBrokerUri;

    /** MQTT client ID. */
    const char* myClientId;

    /** Boolean flag tracking the connection status. */
    bool myConnected;
                                 
    /** Maximum stored topic length including null terminator. */
    static constexpr std::uint16_t topicBufSize{64U};

    /** Maximum stored payload length including null terminator. */
    static constexpr std::uint16_t payloadBufSize{128U};

    /** Last received MQTT topic. */
    char myLastTopic[topicBufSize];

    /** Last received MQTT payload. */
    char myLastPayload[payloadBufSize];

    /** True when an unread MQTT message is stored. */
    bool myMessageAvailable;
};
} // namespace driver::mqtt
