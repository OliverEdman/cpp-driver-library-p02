/**
 * @brief MQTT driver interface
 */
#pragma once

#include <cstdint>

#include "driver/mqtt/interface.h"

namespace driver::mqtt
{
/**
 * @brief MQTT driver interface
 * 
 *        This class is non-copyable and non-movable.
 */
class Esp32s3 final : public Interface
{
public:
    /**
     * @brief Constructor
     */
    Esp32s3() noexcept
        : myConnected{false}
    {}

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
     *        shouled be called periodically from the main loop/task.
     */
    void loop() noexcept override;

    Stub(const Stub&)            = delete; // No copy constructor.
    Stub(Stub&&)                 = delete; // No move constructor.
    Stub& operator=(const Stub&) = delete; // No copy assignment.
    Stub& operator=(Stub&&)      = delete; // No move assignment.

private:
    /** Simulated state (True = connected, false = disconnected. ) */
    bool myConnected;
}
}; // namespace driver::mqtt