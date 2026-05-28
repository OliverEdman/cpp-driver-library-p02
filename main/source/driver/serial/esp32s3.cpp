/**
 * @brief Serial driver ESP32-S3 implementation.
 */
#include <cstdint>
#include <cstring>

#include "driver/serial/esp32s3.h"
#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"

namespace driver::serial
{
// -----------------------------------------------------------------------------
Esp32s3::Esp32s3(const Config& config) noexcept
    : myConfig{config}
    , myQueue{nullptr}
    , myConnected{false}
{}

// -----------------------------------------------------------------------------
Esp32s3::~Esp32s3() noexcept
{
    if (myConnected)
    {
        disconnect();
    }
}

// -----------------------------------------------------------------------------
bool Esp32s3::connect() noexcept
{
    const uart_config_t uartConfig = {
        .baud_rate  = myConfig.baudRate,
        .data_bits  = UART_DATA_8_BITS,
        .parity     = UART_PARITY_DISABLE,
        .stop_bits  = UART_STOP_BITS_1,
        .flow_ctrl  = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    if (uart_param_config(myConfig.port, &uartConfig) != ESP_OK)
    {
        return false;
    }

    if (uart_set_pin(myConfig.port,
                     myConfig.txPin,
                     myConfig.rxPin,
                     UART_PIN_NO_CHANGE,
                     UART_PIN_NO_CHANGE) != ESP_OK)
    {
        return false;
    }

    if (uart_driver_install(myConfig.port,
                            static_cast<int>(myConfig.rxBufSize),
                            0,          // TX buffer: 0 = write blocks until done
                            QueueDepth, // Event queue depth
                            &myQueue,   // Queue handle (needed for pattern detection)
                            0)          // Interrupt flags
        != ESP_OK)
    {
        return false;
    }

    // Enable hardware detection of '\n' as the message delimiter.
    if (uart_enable_pattern_det_baud_intr(myConfig.port, '\n', 1, 9, 0, 0) != ESP_OK)
    {
        uart_driver_delete(myConfig.port);
        return false;
    }

    // Align the pattern queue size with the event queue depth.
    uart_pattern_queue_reset(myConfig.port, QueueDepth);

    myConnected = true;
    return true;
}

// -----------------------------------------------------------------------------
void Esp32s3::disconnect() noexcept
{
    uart_driver_delete(myConfig.port);
    myQueue     = nullptr;
    myConnected = false;
}

// -----------------------------------------------------------------------------
void Esp32s3::write(std::uint8_t byte) noexcept
{
    if (!myConnected) { return; }
    uart_write_bytes(myConfig.port, &byte, 1U);
}

// -----------------------------------------------------------------------------
std::uint16_t Esp32s3::write(const char* msg) noexcept
{
    if (!myConnected)  { return 0U; }
    if (nullptr == msg) { return 0U; }

    const int written = uart_write_bytes(myConfig.port, msg, std::strlen(msg));
    return (written < 0) ? 0U : static_cast<std::uint16_t>(written);
}

// -----------------------------------------------------------------------------
std::uint8_t Esp32s3::read() noexcept
{
    if (!myConnected) { return 0U; }

    std::uint8_t byte{};
    uart_read_bytes(myConfig.port, &byte, 1U, pdMS_TO_TICKS(10U));
    return byte;
}

// -----------------------------------------------------------------------------
std::uint16_t Esp32s3::read(char* buf, std::uint16_t maxLen) noexcept
{
    if (!myConnected)   { return 0U; }
    if (nullptr == buf) { return 0U; }
    if (0U == maxLen)   { return 0U; }

    // Check how many bytes are waiting before the detected '\n'.
    // Returns -1 if no complete message is available yet.
    const int patternPos = uart_pattern_pop_pos(myConfig.port);
    if (patternPos < 0) { return 0U; }

    // Cap the read length to leave room for the null terminator.
    const std::uint16_t limit{static_cast<std::uint16_t>(maxLen - 1U)};
    const std::uint16_t toRead{(static_cast<std::uint16_t>(patternPos) < limit)
                                ? static_cast<std::uint16_t>(patternPos)
                                : limit};

    // Read the full message in one call.
    const int result = uart_read_bytes(myConfig.port,
                                       reinterpret_cast<std::uint8_t*>(buf),
                                       toRead,
                                       pdMS_TO_TICKS(100U));

    // Consume the '\n' from the buffer so it doesn't pollute the next read.
    std::uint8_t newline{};
    uart_read_bytes(myConfig.port, &newline, 1U, pdMS_TO_TICKS(10U));

    const std::uint16_t bytesRead{(result < 0) ? 0U : static_cast<std::uint16_t>(result)};
    buf[bytesRead] = '\0';
    return bytesRead;
}

// -----------------------------------------------------------------------------
bool Esp32s3::isDataAvailable() const noexcept
{
    if (!myConnected) { return false; }

    // Returns the position of the next detected '\n', or -1 if none found.
    // A non-negative result means a complete message is ready to read.
    return uart_pattern_get_pos(myConfig.port) >= 0;
}

// -----------------------------------------------------------------------------
bool Esp32s3::isInitialized() const noexcept
{
    return myConnected;
}

} // namespace driver::serial
