/**
 * @brief A serial driver for the ESP32-S3.
 */
#pragma once

#include <cstdint>

#include "driver/serial/interface.h"
#include "driver/uart.h"

namespace driver::serial
{

/**
 * @brief Configuration for the ESP32-S3 serial driver.
 */
struct Config
{
    /** UART port number (e.g. UART_NUM_1). */
    uart_port_t port;

    /** TX GPIO pin number. */
    int txPin;

    /** RX GPIO pin number. */
    int rxPin;

    /** Baud rate (e.g. 115200). */
    int baudRate;

    /** RX ring buffer size in bytes (must be > 0). */
    uint32_t rxBufSize;
};

/**
 * @brief Serial driver for ESP32-S3.
 *
 *        This class is non-copyable and non-movable.
 */
class Esp32s3 final: public Interface
{
public:
    /**
     * @brief Constructor.
     *
     * @param[in] config Driver configuration.
     */
    explicit Esp32s3(const Config& config) noexcept;

    /**
     * @brief Destructor. Disconnects automatically if still connected.
     */
    ~Esp32s3() noexcept override;

    /**
     * @brief Connect device (installs UART driver, configures pins).
     *
     * @return True on success, false on failure.
     */
    bool connect() noexcept override;

    /**
     * @brief Disconnect device (uninstalls UART driver).
     */
    void disconnect() noexcept override;

    /**
     * @brief Write a single byte.
     *
     * @param[in] byte The byte to send.
     */
    void write(std::uint8_t byte) noexcept override;

    /**
     * @brief Write a null-terminated string.
     *
     * @param[in] msg The message to send.
     *
     * @return The number of transmitted bytes, or 0 on error.
     */
    std::uint16_t write(const char* msg) noexcept override;

    /**
     * @brief Read a single byte (blocks up to 10 ms).
     *
     * @return The received byte, or 0 if none available.
     */
    std::uint8_t read() noexcept override;

    /**
     * @brief Check if data is available in the RX buffer.
     *
     * @return True if at least one byte is waiting, false otherwise.
     */
    bool isDataAvailable() const noexcept override;

    Esp32s3(const Esp32s3&)            = delete;
    Esp32s3(Esp32s3&&)                 = delete;
    Esp32s3& operator=(const Esp32s3&) = delete;
    Esp32s3& operator=(Esp32s3&&)      = delete;

private:
    /** Driver configuration. */
    Config myConfig;

    /** True if the UART driver is installed and active. */
    bool myConnected;
};

} // namespace driver::serial
