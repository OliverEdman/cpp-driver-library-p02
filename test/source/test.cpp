#include <cstdio>

#include "system/pin_manager/esp32s3.h"
#include "test/pin_manager.h"

int main()
{
    auto& pinManager = system::pin_manager::Esp32s3::instance();
    if (!test::runPinManagerTest(pinManager)) { return -1; }

    return 0;
}