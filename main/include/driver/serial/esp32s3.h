/**
 * @brief A serial driver for the ESP32-S3.
 */
#pragma once

#include <cstdint>

#include "driver/serial/interface.h"
#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

namespace driver::serial
{

/**
 * @brief Configuration for the ESP32-S3 serial driver.
 */
struct Config
{
    /** UART port number (e.g. UART_NUM_1). Ignored when useUsbJtag is true. */
    uart_port_t port;

    /** TX GPIO pin number. Ignored when useUsbJtag is true. */
    int txPin;

    /** RX GPIO pin number. Ignored when useUsbJtag is true. */
    int rxPin;

    /** Baud rate (e.g. 115200). Ignored when useUsbJtag is true. */
    int baudRate;

    /** RX ring buffer size in bytes (must be > 0). Ignored when useUsbJtag is true. */
    uint32_t rxBufSize;

    /** Use built-in USB-Serial-JTAG instead of a UART port. */
    bool useUsbJtag{false};
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
     * @brief Read a newline-terminated message into a buffer.
     *
     *        Reads bytes until '\n' is received, the buffer is full, or
     *        a per-byte timeout (10 ms) elapses with no data. The result
     *        is always null-terminated.
     *
     * @param[out] buf    Destination buffer.
     * @param[in]  maxLen Size of the destination buffer (including '\0').
     *
     * @return Number of bytes written, excluding the null terminator.
     */
    std::uint16_t read(char* buf, std::uint16_t maxLen) noexcept override;

    /**
     * @brief Check if a complete newline-terminated message is available.
     *
     * @return True if a full message is waiting, false otherwise.
     */
    bool isDataAvailable() const noexcept override;

    /**
     * @brief Check if the driver is initialized (connected).
     *
     * @return True if initialized, false otherwise.
     */
    bool isInitialized() const noexcept override;

    Esp32s3(const Esp32s3&)            = delete;
    Esp32s3(Esp32s3&&)                 = delete;
    Esp32s3& operator=(const Esp32s3&) = delete;
    Esp32s3& operator=(Esp32s3&&)      = delete;

private:
    /** Event queue depth for pattern detection. */
    static constexpr int QueueDepth{10};

    /** Max line length for USB-Serial-JTAG accumulator. */
    static constexpr std::uint16_t LineBufSize{64};

    /** Driver configuration. */
    Config myConfig;

    /** FreeRTOS event queue used for pattern detection. */
    QueueHandle_t myQueue;

    /** True if the UART driver is installed and active. */
    bool myConnected;

    /** Accumulated partial line for USB-Serial-JTAG mode. */
    char myLineBuf[LineBufSize];

    /** Number of valid bytes in myLineBuf. */
    std::uint16_t myLineLen;
};

} // namespace driver::serial
