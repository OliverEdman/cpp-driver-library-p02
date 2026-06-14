/**
 * @brief Serial driver interface for simulation.
 *
 */
#pragma once

//! @note Sort the headers, please.
#include <cstdio>
#include <cstdint>

#include "driver/serial/interface.h"

namespace driver::serial
{
/**
 * @brief Serial interface.
 * 
 *        This class is non-copyable, non-movable, and non-inheritable.
 */
class Stub final: public Interface
{
public:
    /**
     * @brief Constructor.
     */
    Stub() noexcept;

    /**
     * @brief Destructor.
     */
    ~Stub() noexcept override;

    /**
     * @brief Connect the simulated serial device.
     * 
     * @return True on success, false on failure.
     */
    bool connect() noexcept override;

    /**
     * @brief Disconnect the simulated serial device.
     */
    void disconnect() noexcept override;

    /**
     * @brief Write a single byte to the simulated output.
     * 
     * @param[in] byte The byte to send.
     */
    void write(std::uint8_t byte) noexcept override;

    /**
     * @brief Write a message.
     * 
     * @param[in] msg The message to send.
     * 
     * @return The number of bytes successfully transmitted.
     */
    std::uint16_t write(const char* msg) noexcept override;

    /**
     * @brief Read a single byte from the simulated buffer.
     * 
     * @return The received byte value, or 0 if no data is available.
     */
    std::uint8_t read() noexcept override;

    /**
     * @brief Read a newline-terminated message into a buffer.
     * 
     *        Read characters from the simulated input buffer until '\\n' is
     *        found, the buffer becomes full, or data runs out.
     * 
     *        The output is always null-terminated.
     * 
     * @param[out] buf Destination buffer to write the text into.
     * @param[in] maxLen The maximum size of the buffer (including '\0').
     * 
     * @return Number of bytes read, excluding the null terminator.
     */
    std::uint16_t read(char* buf, std::uint16_t maxLen) noexcept override;

    /**
     * @brief Check if simulated data is available to read.
     * 
     * @return True if data is available, false otherwise.
     */
    bool isDataAvailable() const noexcept override;

    /**
     * @brief Check if the simulated serial driver is initialized and active.
     * 
     * @return True if connected, false otherwise.
     */
    bool isInitialized() const noexcept override;

    /**
     * @brief Simulate incoming data by loading it into the buffer.
     * 
     * @param[in] data Pointer to the input data array.
     * @param[in] dataLen The number of bytes in the data array.
     * 
     * @return The number of bytes successfully copied into the buffer.
     */
    std::uint8_t simulateInput(const std::uint8_t* data, std::uint8_t dataLen) noexcept;

    // Delete no/copy move constructors and operators.
    Stub(const Stub&)            = delete;
    Stub(Stub&&)                 = delete;
    Stub& operator=(const Stub&) = delete; 
    Stub& operator=(Stub&&)      = delete; 


private:
    //! @note Please omit @brief for one-liners.
    /** @brief Maximum simulated buffer size. */
    static constexpr std::uint8_t BufSize{100U};

    /** @brief Buffer used to store simulated incoming data. */
    std::uint8_t myBuf[BufSize];

    /** @brief Current number of valid bytes stored in the buffer. */
    std::uint8_t myBufLen;

    /** @brief Current read position index inside the buffer*/
    std::uint8_t myBufIndex;

    /** @brief Flag tracking if data is ready to be read. */
    bool myDataAvailable;

    /** @brief Flag tracking if the simulated device is connected*/
    bool myConnected;
};
}// namespace driver:: serial
