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
Esp32s3::~Esp32s3() noexcept {}

// -----------------------------------------------------------------------------
bool Esp32s3::connect() noexcept { return true; }

// -----------------------------------------------------------------------------
void Esp32s3::disconnect() noexcept {}

// -----------------------------------------------------------------------------
void Esp32s3::write(std::uint8_t byte) noexcept {}

// -----------------------------------------------------------------------------
std::uint16_t Esp32s3::write(const char* msg) noexcept { return 0U; }

// -----------------------------------------------------------------------------
std::uint8_t Esp32s3::read() noexcept { return 0U; }

// -----------------------------------------------------------------------------
bool Esp32s3::isDataAvailable() const noexcept { return myDataAvailable; };
}// namespace driver:: serial