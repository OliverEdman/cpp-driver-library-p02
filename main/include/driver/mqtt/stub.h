/*
 * @file stub.h
 * @brief MQTT driver stub interface for simulation.
 */
#pragma once

#include <cstdint>

#include "driver/mqtt/interface.h"

namespace driver::mqtt
{
/**
 * @brief MQTT driver stub interface for simulation.
 * This class is non-copyable and non-movable.
 */
class Stub final : public Interface
{
public:
     /**
     * @brief Constructor.
     * Initializes the simulated connection state to disconnected.
     */ 
    Stub() noexcept
        : myConnected{false}
    {}

    /**
     * @brief Destructor.
     */
    ~Stub() noexcept override = default;

    /**
     * @brief Connect to the simulated MQTT broker.
     * @return True if connection succeeded, false otherwise.
     */
    bool connect() noexcept override{
        myConnected = true;
        return true;
    }

    /**
     * @brief Disconnect from the simulated MQTT broker.
     */
    void disconnect() noexcept override{
        myConnected = false;
    }

    /**
     * @brief Check the simulated connection state.
     * @return True if currently simulated is connected, false otherwise.
     */
    bool isConnected() const noexcept override{
        return myConnected;
    }

    /**
     * @brief Publish MQTT message.
     * @param[in] topic MQTT topic.
     * @param[in] payload Message payload.
     * @return True if the simulated was connected, false if disconnected.
     */
    bool publish(const char* topic, const char* payload) noexcept override{
        (void)topic;
        (void)payload;

        return myConnected;
    }

    /**
     * @brief Simulate subscribe to an MQTT topic.
     * @param[in] topic MQTT topic.
     * @return True if the simulated connected, false if disconnected.
     */
    bool subscribe(const char* topic) noexcept override{
        (void)topic;

        return myConnected;
    }

    /**
     * @brief Process simulated MQTT events and incoming messages.
     * This function does nothing since the simulated stub has no real backround tasks.
     */
    void loop() noexcept override{
        // No operation in Stub.
    }

    /**
     * @brief Read a simulated MQTT message.
     *
     * The minimal stub currently has no queued messages, so this always returns false.
     */
    bool readMessage(char* topic,
                     std::uint16_t topicMaxLen,
                     char* payload,
                     std::uint16_t payloadMaxLen) noexcept override
    {
        (void)topic;
        (void)topicMaxLen;
        (void)payload;
        (void)payloadMaxLen;

        return false;
    }


    Stub(const Stub&)            = delete;
    Stub(Stub&&)                 = delete;
    Stub& operator=(const Stub&) = delete;
    Stub& operator=(Stub&&)      = delete;

private:
    /** @brief Simulated state (True = connected, false = disconnected. ) */
    bool myConnected;
};
} // namespace driver::mqtt
