/**
 * @brief A serial driver for the ESP32-s3.
 */
#pragma once

#include <cstdint>

#include "driver/serial/interface.h"
#include "driver/uart.h"

namespace driver::serial
{
class Esp32 final: public interface
{
public:
    /**
     * @brief Constructor.
     */
    Esp32() noexcept override;
    
    /**
     * @brief Deconstructor.
     */
    ~Esp32() noexcept override; 

    /**
     * @brief Connect device.
     * 
     * @return True on success, false on failure.
     */
    bool connect() noexcept override;

    /**
     * @brief Disconnect device.
     */
    void disconnect() noexcept override;

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
     */
    std::uint16_t write(const char* msg) noexcept override;

    /** 
     * @brief Read a byte.
     * 
     * @return The read byte.
     */
    std::uint8_t read() noexcept override;

    /**
     * @brief Check if data is available.
     * 
     * @return Return true if data is available, otherwise false.
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
}  
} // namespace driver::serial