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
//! @note Nice struct! For simplicity, I would initialize the member variables inline
//!       when using a struct like this, e.g. int txPin{} => if you create a config
//!       like this: Config config{}, then all parameters will be initialized.
//!       Note: For a class, I would suggest adding a constructor instead.
struct Config
{
    //! @note As I said before, you may skip @brief for one-liners.
    /** @brief UART port number (e.g. UART_NUM_1). Ignored when useUsbJtag is true. */
    uart_port_t port;

    /** @brief TX GPIO pin number. Ignored when useUsbJtag is true. */
    //! @note I guess you're using ints to match the ESP32-S3 functions. That's fine.
    //!       If this wasn't the case, I would suggest using uints such as std::uint32_t.
    int txPin;

    /** @brief RX GPIO pin number. Ignored when useUsbJtag is true. */
    int rxPin;

    /** @brief Baud rate (e.g. 115200). Ignored when useUsbJtag is true. */
    int baudRate;

    /** @brief RX ring buffer size in bytes (must be > 0). Ignored when useUsbJtag is true. */
    //! @note Use std::uint32_t, not the C alias uint32_t (skip the std:: prefix).
    uint32_t rxBufSize;

    /** @brief Use built-in USB-Serial-JTAG instead of a UART port. */
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
     * @return True if successful, false on failure.
     */
    bool connect() noexcept override;

    /**
     * @brief Disconnect device and uninstall the UART driver
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
     * @return The number of bytes successfully sent, or 0 on error.
     */
    std::uint16_t write(const char* msg) noexcept override;

    /**
     * @brief Read a single byte (blocks for up to 10 ms).
     * 
     * @return The received byte value, or 0 if no data is available.
     */
    std::uint8_t read() noexcept override;

    /**
     * @brief Read a newline-terminated message into a buffer.
     * 
     *        Reads characters (bytes) until '\n' is found, the buffer becomes full, or
     *        a per-byte timeout (10 ms) occurs. The output is always null-terminated.
     * 
     * @param[out] buf the Destination buffer to write the text into.
     * @param[in] maxLen The maxinum size of the buffer (including '\0').
     * 
     * @return Number of bytes read, excluding the null terminator.
     */
    std::uint16_t read(char* buf, std::uint16_t maxLen) noexcept override;

    /**
     * @brief Check if a complete newline-terminated message is ready to be read.
     * 
     * @return True if a full message is waiting in the buffer, false otherwise.
     */
    bool isDataAvailable() const noexcept override;

    /**
     * @brief Check if the serial driver is initialized (connected) and active.
     * 
     * @return True if connected and ready for use, false otherwise.
     */
    bool isInitialized() const noexcept override;

    // Delete copy/move constructors and operators.
    Esp32s3(const Esp32s3&)            = delete;
    Esp32s3(Esp32s3&&)                 = delete;
    Esp32s3& operator=(const Esp32s3&) = delete;
    Esp32s3& operator=(Esp32s3&&)      = delete;

private:
    /** @brief Event queue depth for pattern detection. */
    static constexpr int QueueDepth{10};

    /** @brief Max line length for USB-Serial-JTAG accumulator. */
    static constexpr std::uint16_t LineBufSize{64};

    /** @brief Driver configuration. */
    Config myConfig;

    /** @brief FreeRTOS event queue used for pattern detection. */
    QueueHandle_t myQueue;

    /** @brief True if the UART driver is installed and active. */
    bool myConnected;

    /** @brief Accumulated partial line for USB-Serial-JTAG mode. */
    char myLineBuf[LineBufSize];

    /** @brief Number of valid bytes in myLineBuf. */
    std::uint16_t myLineLen;
};
} // namespace driver::serial
