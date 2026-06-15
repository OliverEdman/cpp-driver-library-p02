//! @note No more @file, no more @file sung as No More Lies by Iron Maiden 
//!       (Anthon, you know what I mean).
/**
 * @file direction.h
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
    //! @note Enums are usually commented like this.
    Input,       ///< Standard digital input (floating).
    InputPullup, ///< Digital input with an internal pull-up resistor enabled.
    Output,      ///< Standard digital output.
};
} // namespace driver::gpio
