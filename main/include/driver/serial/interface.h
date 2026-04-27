/**
 * @brief Serial Interface.
 */
#pragma once

#include <cstdint>

namespace driver::serial
{
/**
 * @brief Serial Interface
 */
class Interface
{
public:
    /**
     * @brief Destructor.
     */
    virtual ~Interface() noexcept = default;

    /**
     * @brief Connect device.
     * 
     * @return True on success, false on failure.
     */
    virtual bool connect() noexcept = 0;

    /**
     * @brief Disonnect device.
     * 
     */
    virtual void Disconnect() noexcept = 0;

    /**
     * @brief Write a byte.
     * 
     * @param[in] byte The byte to send.
     */
    virtual void write(std::uint8_t byte) noexcept = 0;

    /**
     * @brief Write a message.
     * 
     * @param[in] msg The message to send.
     * 
     * @return The number of transmitted bytes.
     */
    virtual std::uint16_t write(const char* msg) noexcept = 0;

    /**
     * @brief Read a byte.
     * 
     * @return Received byte.
     */
    virtual std::uint8_t read() noexcept = 0;

        /**
     * @brief Check if data is available.
     * 
     * @return True if data is available, false otherwise.
     */
    virtual bool isDataAvailable() const noexcept = 0;
};
}// namespace driver:: serial