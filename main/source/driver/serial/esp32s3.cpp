/**
 * @brief Serial driver esp32s3 implementation details.
 * 
 */
#include <cstdio>
#include <cstdint>

#include "driver/serial/esp32s3.h"
#include "driver/uart.h"

namespace driver::serial
{
// -----------------------------------------------------------------------------
Esp32s3::Esp32s3() noexcept
    : myBuf{}
    , myBufLen{}
    , myBufIndex{}
    , myDataAvailable{false}
    , myConnected{false}
{}

// -----------------------------------------------------------------------------
Esp32s3::~Esp32s3() noexcept
{}

// -----------------------------------------------------------------------------
bool Esp32s3::connect() noexcept
{
    myConnected = true;
    return true;
}

// -----------------------------------------------------------------------------
void Esp32s3::disconnect() noexcept
{
    myConnected = false;
}

// -----------------------------------------------------------------------------
void Esp32s3::write(std::uint8_t byte) noexcept
{
    // Skip write if the device isn't connected.
    if (!myConnected) { return; }

    // Print the byte as an unsigned integer.

}

// -----------------------------------------------------------------------------
std::uint16_t Esp32s3::write(const char* msg) noexcept
{
    // Return 0 if the device isn't connected.
    if (!myConnected) { return 0U; }

    // Return 0 if the message is invalid.
    if (nullptr == msg) { return 0U; }

    // String index + length.
    std::uint16_t i{};

    // Pint each character one by one.
    // Simulate that the bytes are sent on at a time).
    for (i = 0U; msg[i] != '\0'; ++i)
    {
        // std::printf("%c", msg[i]);
    }

    // Return the number of written bytes.
    return i;
}

// -----------------------------------------------------------------------------
std::uint8_t Esp32s3::read() noexcept
{
    // Return 0 if the device isn't connected.
    if (!myConnected) { return 0U; }
    
    // Return 0 if no data is available.
    if (!myDataAvailable) { return 0U; }

    // Read the next byte in the buffer.
    const std::uint8_t byte{myBuf[myBufIndex]};

    // Increment the buffer index to point at the next byte.
    // Mark that no data is available if all bytes have been sent.
    if (++myBufIndex >= myBufLen)
    {
        myDataAvailable = false;
        myBufIndex      = 0U;
    }
    // Return the retrieved byte.
    return byte;
}

// -----------------------------------------------------------------------------
bool Esp32s3::isDataAvailable() const noexcept { return myDataAvailable; };
}// namespace driver:: serial