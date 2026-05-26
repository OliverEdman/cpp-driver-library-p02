/**
 * @brief Serial driver ESP32-S3 implementation.
 */
#include <cstdint>
#include <cstring>

#include "driver/serial/esp32s3.h"
#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

namespace driver::serial
{
// -----------------------------------------------------------------------------
Esp32s3::Esp32s3(const Config& config) noexcept
    : myConfig{config}
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
                            0,       // TX buffer: 0 = write blocks until done
                            0,       // Queue size: 0 = no event queue
                            nullptr, // Queue handle
                            0)       // Interrupt flags
        != ESP_OK)
    {
        return false;
    }

    myConnected = true;
    return true;
}

// -----------------------------------------------------------------------------
void Esp32s3::disconnect() noexcept
{
    uart_driver_delete(myConfig.port);
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
bool Esp32s3::isDataAvailable() const noexcept
{
    if (!myConnected) { return false; }

    size_t buffered{};
    uart_get_buffered_data_len(myConfig.port, &buffered);
    return buffered > 0U;
}

} // namespace driver::serial
