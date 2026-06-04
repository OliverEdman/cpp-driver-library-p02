/**
 * @file esp32s3.h
 * @brief MQTT driver for the ESP32-S3.
 */
#pragma once

#include <cstdint>

/**
 * @brief Include ESP-IDF MQTT C API with C linkage.
 */
extern "C" {
#include "mqtt_client.h"
}

#include "driver/mqtt/interface.h"

namespace driver::mqtt
{
/**
 * @brief MQTT driver implementation for ESP32-S3.
 * This class uses the built in ESP-IDF functions to talk to an MQTT broker over the network.
 * It is explicitly non-copyable and non-movable
 */
class Esp32s3 final : public Interface
{
public:
    /**
     * @brief Constructor
     * 
     * @param[in] brokerUri MQTT broker URI.
     * @param[in] clientId MQTT client ID.
     */
    Esp32s3(const char* brokerUri,
            const char* clientId) noexcept;

    /**
     * @brief Destructor.
     */
    ~Esp32s3() noexcept override;

    /**
     * @brief Connect to the MQTT broker.
     * @return True if connection succeeded, false otherwise.
     */
    bool connect() noexcept override;

    /**
     * @brief Disconnect from the MQTT broker.
     */
    void disconnect() noexcept override;

    /**
     * @brief Check the current connection state.
     * @return True if currently connected to the broker, false otherwise.
     */
    bool isConnected() const noexcept override;

    /**
     * @brief Publish MQTT message.
     * @param[in] topic MQTT topic.
     * @param[in] payload Message payload.
     * @return True if the message was successfully published, false otherwise.
     */
    bool publish(const char* topic, const char* payload) noexcept override;

    /**
     * @brief Subscribe to a specific MQTT topic.
     * @param[in] topic MQTT topic.
     * @return True if subscription succeeded, false otherwise.
     */
    bool subscribe(const char* topic) noexcept override;

    /**
     * @brief Process MQTT events and incoming messages.
     * should be called periodically from the main loop/task.
     */
    void loop() noexcept override;

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
    static void mqttEventHandler(void* handler_args,
                                 esp_event_base_t base,
                                 int32_t event_id,
                                 void* event_data);

    /** @brief ESP-IDF MQTT client handle. */
    esp_mqtt_client_handle_t myHandle;

    /** @brief MQTT broker URI. */
    const char* myBrokerUri;

    /** @brief MQTT client ID. */
    const char* myClientId;

    /** @brief Boolean flag tracking the connection status. */
    bool myConnected;
                                 
};
} // namespace driver::mqtt
