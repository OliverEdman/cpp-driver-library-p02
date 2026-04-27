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
{

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
void Stub::Disconnect() noexcept
{
    myConnected = false;
    std::printf("Serial device disconnected!\n")
}

// -----------------------------------------------------------------------------
void Stub::write(std::uint8_t byte) noexcept
{
    
}

// -----------------------------------------------------------------------------
std::uint16_t Stub::write(const char* msg) noexcept
{
    return msg[0];
}

// -----------------------------------------------------------------------------
std::uint8_t Stub::read() noexcept
{
    return 0U;
}

// -----------------------------------------------------------------------------
bool Stub::isDataAvailable() const noexcept
{
    return myDataAvailable;
}

};
}// namespace driver:: serial