/**
 * @brief Serial driver stub implementation details.
 * 
 */
#include <cstdio>
#include <cstdint>

#include "driver/serial/stub.h"

namespace driver::serial
{
// -----------------------------------------------------------------------------
Stub::Stub() noexcept
    : myBuf{}
    , myBufLen{}
    , myBufIndex{}
    , myDataAvailable{false}
    , myConnected{false}
{
    std::printf("Created new serial stub instance!\n");
}

// -----------------------------------------------------------------------------
Stub::~Stub() noexcept
{
    std::printf("Destroying serial stub instance!\n");
}

// -----------------------------------------------------------------------------
bool Stub::connect() noexcept
{
    myConnected = true;
    std::printf("Serial device connected!\n");
    return true;
}

// -----------------------------------------------------------------------------
void Stub::disconnect() noexcept
{
    myConnected = false;
    std::printf("Serial device disconnected!\n")
}

// -----------------------------------------------------------------------------
void Stub::write(std::uint8_t byte) noexcept
{
    // Skip write if the device isn't connected.
    if (!myConnected) { return; }

    // Print the byte as an unsigned integer.
    std::printf("%u", byte);

}

// -----------------------------------------------------------------------------
std::uint16_t Stub::write(const char* msg) noexcept
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
        std::printf("%c", msg[i]);
    }

    // Return the number of written bytes.
    return i;
}

// -----------------------------------------------------------------------------
std::uint8_t Stub::read() noexcept
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
bool Stub::isDataAvailable() const noexcept
{ return myDataAvailable; };

// -----------------------------------------------------------------------------
std::uint8_t Stub::simulateInput(const std::uint* data, std::uint8_t dataLen) noexcept
{
    // Return 0 if the device isn't connected.
    if (!myConnected) { return 0U; }

    // Return 0 if input data is missing.
    if ((nullptr == data) || (0U == dataLen)) { return 0U; }

    // Compute the number of bytes to copy
    const std::uint8_t bytesToCopy{myBufLen < dataLen ? BufSize : dataLen};

    // Copy data from the input array to our buffer.
    for (std::uint8_t i{}; i < bytesToCopy; ++i)
    {
        myBuf[i] = data[i];
    }
    // Save the number of bytes in the buffer and indicate that data is available.
    myBufLen = bytesToCopy;
    myDataAvailable = true;
    return bytesToCopy;
}
}// namespace driver:: serial