/**
 * @brief GPIO direction type.
 */
#pragma once

#include <cstdint>

namespace driver::gpio
{
/**
 * @brief Enumeration of data direction alternatives.
 */
enum class Direction : std::uint8_t
{
    Input,
    InputPullup,
    Output,
};
} // namespace driver::gpio
