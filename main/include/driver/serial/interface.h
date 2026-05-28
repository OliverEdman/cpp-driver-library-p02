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
    virtual void disconnect() noexcept = 0;

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
     * @brief Read a single byte.
     *
     * @return Received byte, or 0 if none available.
     */
    virtual std::uint8_t read() noexcept = 0;

    /**
     * @brief Read a newline-terminated message into a buffer.
     *
     *        Reads bytes until a '\n' is received, the buffer is full
     *        (maxLen - 1 bytes), or no more data is available. The result
     *        is always null-terminated.
     *
     * @param[out] buf    Destination buffer.
     * @param[in]  maxLen Size of the destination buffer (including '\0').
     *
     * @return Number of bytes written, excluding the null terminator.
     */
    virtual std::uint16_t read(char* buf, std::uint16_t maxLen) noexcept = 0;

        /**
     * @brief Check if data is available.
     *
     * @return True if data is available, false otherwise.
     */
    virtual bool isDataAvailable() const noexcept = 0;

    /**
     * @brief Check if the device is initialized (connected).
     *
     * @return True if initialized, false otherwise.
     */
    virtual bool isInitialized() const noexcept = 0;
};
}// namespace driver:: serial