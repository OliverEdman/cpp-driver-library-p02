#pragma once

/** Pin manager interface. */
namespace system::pin_manager
{
class Interface;
} // namespace system::pin_manager

namespace test
{
bool runPinManagerTest(system::pin_manager::Interface& manager) noexcept;
} // namespace test