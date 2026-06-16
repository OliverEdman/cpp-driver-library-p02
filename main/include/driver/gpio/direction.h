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
    Input,       ///< Standard digital input (floating).
    InputPullup, ///< Digital input with an internal pull-up resistor enabled.
    Output,      ///< Standard digital output.
};
} // namespace driver::gpio
