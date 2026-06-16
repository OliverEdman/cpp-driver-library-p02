/**
 * @brief Interface for the Serial driver.
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
     * @return True if successful, false on failure.
     */
    virtual bool connect() noexcept = 0;

    /**
     * @brief Disconnect device.
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
     * @return The number of bytes successfully sent, or 0 on error.
     */
    virtual std::uint16_t write(const char* msg) noexcept = 0;

    /**
     * @brief Read a single byte.
     *
     * @return The received byte value, or 0 if no data is available.
     */
    virtual std::uint8_t read() noexcept = 0;

     /**
     * @brief Read a newline-terminated message into a buffer.
     *        
     *        Read characters until a '\n' is found, the buffer becomes full, or
     *        a timeout accours. The output is always null-terminated.
     * 
     * @param[out] buf The destination buffer to write the text into.
     * @param[in] maxLen The maximum size of the buffer (including '\0').
     * 
     * @return The number of bytes read, excluding the null terminator.
     */
    virtual std::uint16_t read(char* buf, std::uint16_t maxLen) noexcept = 0;

     /**
     * @brief Check if a complete newline-terminated message is ready to be read.
     *
     * @return True if a full line is waiting in the buffer, false otherwise.
     */
    virtual bool isDataAvailable() const noexcept = 0;

    /**
     * @brief Check if the device is initialized (connected).
     *
     * @return True if connected and ready for use, false otherwise.
     */
    virtual bool isInitialized() const noexcept = 0;
};
} // namespace driver:: serial
