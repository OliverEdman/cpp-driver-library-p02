/*
 * @file interface.h
 * @brief MQTT driver interface
 */
#pragma once

#include <cstdint>

namespace driver::mqtt
{
/**
 * @brief MQTT driver interface
 */
class Interface
{
public:
    /**
     * @brief Destructor.
     */
    virtual ~Interface() noexcept = default;

    /**
     * @brief Connect to the MQTT broker.
     * @return True if the connection succeeded, false otherwise.
     */
    virtual bool connect() noexcept = 0;

    /**
     * @brief Disconnect from the MQTT broker.
     */
    virtual void disconnect() noexcept = 0;

    /**
     * @brief Check connection state.
     * @return True if currently connected to the broker, false otherwise.
     */
    virtual bool isConnected() const noexcept = 0;

    /**
     * @brief Publish MQTT message.
     * @param[in] topic MQTT topic.
     * @param[in] payload Message payload.
     * @return True if successful, false otherwise.
     */
    virtual bool publish(const char* topic, const char* payload) noexcept = 0;

    /**
     * @brief Subscribe to MQTT topic.
     * @param[in] topic MQTT topic.
     * @return True if subscription succeeded, false otherwise.
     */
    virtual bool subscribe(const char* topic) noexcept = 0;

    /**
     * @brief Process MQTT events and incoming messages.
     * should be called periodically from the main loop/task.
     */
    virtual void loop() noexcept = 0;

    /**
     * @brief Read the latest received MQTT message.
     *
     * Copies the latest topic and payload into caller-provided buffers.
     * Returns false if no unread message is available.
     *
     * @param[out] topic Buffer receiving the MQTT topic.
     * @param[in] topicMaxLen Size of the topic buffer.
     * @param[out] payload Buffer receiving the MQTT payload.
     * @param[in] payloadMaxLen Size of the payload buffer.
     * @return True if a message was copied, false otherwise.
     */
    virtual bool readMessage(char* topic,
                            std::uint16_t topicMaxLen,
                             char* payload,
                             std::uint16_t payloadMaxLen ) noexcept = 0;
};
} // namespace driver::mqtt
