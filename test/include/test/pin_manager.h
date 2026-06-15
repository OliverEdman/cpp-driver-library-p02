//! @note Missing file header.
#pragma once

/** Pin manager interface. */
namespace sys::pin_manager { class Interface; }

namespace test
{
bool runPinManagerTest(sys::pin_manager::Interface& manager) noexcept;
} // namespace test