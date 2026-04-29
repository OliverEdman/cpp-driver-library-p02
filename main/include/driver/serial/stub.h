/**
 * @brief Serial driver stub.
 * 
 */
#pragma once

#include <cstdio>
#include <cstdint>

#include "driver/serial/interface.h"


namespace driver::serial
{
/**
 * @brief Serial Interface
 *        This class is non-copyable, non-movable and non-inheritable
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
     * @brief Connect device.
     * 
     * @return True on success, false on failure.
     */
    bool connect() noexcept override;

    /**
     * @brief Disonnect device.
     * 
     */
    void Disconnect() noexcept override;

    /**
     * @brief Write a byte.
     * 
     * @param[in] byte The byte to send.
     */
    void write(std::uint8_t byte) noexcept override;

    /**
     * @brief Write a message.
     * 
     * @param[in] msg The message to send.
     * 
     * @return The number of transmitted bytes.
     */
    std::uint16_t write(const char* msg) noexcept override;

    /**
     * @brief Read a byte.
     * 
     * @return Received byte.
     */
    std::uint8_t read() noexcept override;

    /**
     * @brief Check if data is available.
     * 
     * @return True if data is available, false otherwise.
     */
    bool isDataAvailable() const noexcept override;

private:
    /** Buffer size. */
    static constexpr std::uint8_t BufSize{100U};

    /** Serial buffer to simulate input. */
    std::uint8_t myBuf[BufSize];

    /** Buffer length (indicates the number of bytes in the buffer). */
    std::uint8_t myBufLen;

    /** True if data is available, false otherwise. */
    bool myDataAvailable;

    /** True if the device is connected, false otherwise. */
    bool myConnected;
};
}// namespace driver:: serial