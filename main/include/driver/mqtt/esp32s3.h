/**
 * @brief MQTT driver for Esp32s3.
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
 * @brief MQTT driver for Esp32s3
 * 
 *        This class is non-copyable and non-movable.
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
     * 
     * @return True if connection succeeded, false otherwise.
     */
    bool connect() noexcept override;

    /**
     * @brief Disconnect from the MQTT broker.
     */
    void disconnect() noexcept override;

    /**
     * @brief Check connection state.
     * 
     * @return True if connected, false otherwise.
     */
    bool isConnected() const noexcept override;

    /**
     * @brief Publish MQTT message.
     * 
     * @param[in] topic MQTT topic.
     * @param[in] payload Message payload.
     * 
     * @return True if successful, false otherwise.
     */
    bool publish(const char* topic, const char* payload) noexcept override;

    /**
     * @brief Subscribe to MQTT topic.
     * 
     * @param[in] topic MQTT topic.
     * 
     * @return True if subscription succeeded, false otherwise.
     */
    bool subscribe(const char* topic) noexcept override;

    /**
     * @brief Process MQTT events and incoming messages.
     * 
     *        should be called periodically from the main loop/task.
     */
    void loop() noexcept override;

    Esp32s3(const Esp32s3&)            = delete; // No copy constructor.
    Esp32s3(Esp32s3&&)                 = delete; // No move constructor.
    Esp32s3& operator=(const Esp32s3&) = delete; // No copy assignment.
    Esp32s3& operator=(Esp32s3&&)      = delete; // No move assignment.

private:
    /**
     * @brief MQTT event callback handler.
     */
    static void mqttEventHandler(void* handler_args,
                                 esp_event_base_t base,
                                 int32_t event_id,
                                 void* event_data);

    /** ESP-IDF MQTT client handle. */
    esp_mqtt_client_handle_t myHandle;

    /** MQTT broker URI. */
    const char* myBrokerUri;

    /** MQTT client ID. */
    const char* myClientId;

    /** MQTT connection state. */
    bool myConnected;
                                 
};
} // namespace driver::mqtt