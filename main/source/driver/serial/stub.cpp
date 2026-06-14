//! @note File header missing.

//! @brief Sort the headers.
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
    std::printf("Serial device disconnected!\n");
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

    // Print each character one by one.
    // Simulate that the bytes are sent on at a time).
    //! @note i is initialized above => you can omit i = 0U here, i.e. for (; msg[i] != '\0'; ++i)
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
std::uint16_t Stub::read(char* buf, std::uint16_t maxLen) noexcept
{
    //! @note Please place parenthese around conditions when using multiple =>
    //!       you show intend + you don't rely on operator precedence. It works the way it is,
    //!       since == is evaluated before ||, but regular static code analyzers would give you
    //!       a warning for this.
    if (!myConnected || nullptr == buf || 0U == maxLen || !myDataAvailable) 
    { 
        return 0U; 
    }

    //! @note Feel free to use auto here, since you explicitly cast to std::uint16_t =>
    //!       to much "kaka på kaka" => prefer this: 
    //!       const auto limit = static_cast<std::uint16_t>(maxLen - 1U).
    //!       And yes, auto pairs fairly badly with {}, since {1} might be an integer, or it might
    //!       be an array of one element => const auto x{1} might become an initializer list
    //!       => use = when using auto, otherwise use {}.
    const std::uint16_t limit{static_cast<std::uint16_t>(maxLen - 1U)};
    std::uint16_t bytesRead{};

    while ((bytesRead < limit) && myDataAvailable)
    {
        const std::uint8_t byte{myBuf[myBufIndex]};

        // Advance index and mark empty if consumed
        if (++myBufIndex >= myBufLen)
        {
            myDataAvailable = false;
            myBufIndex      = 0U;
        }

        if ('\n' == byte) { break; }
        buf[bytesRead++] = static_cast<char>(byte);
    }

    buf[bytesRead] = '\0';
    return bytesRead;
}

// -----------------------------------------------------------------------------
bool Stub::isDataAvailable() const noexcept
{
    return myDataAvailable;
}

// -----------------------------------------------------------------------------
bool Stub::isInitialized() const noexcept
{
    return myConnected;
}

// -----------------------------------------------------------------------------
std::uint8_t Stub::simulateInput(const std::uint8_t* data, std::uint8_t dataLen) noexcept
{
    // Return 0 if the device isn't connected.
    if (!myConnected) { return 0U; }

    // Return 0 if input data is missing.
    if ((nullptr == data) || (0U == dataLen)) { return 0U; }

    // Compute the number of bytes to copy
    const std::uint8_t bytesToCopy{BufSize < dataLen ? BufSize : dataLen};

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
