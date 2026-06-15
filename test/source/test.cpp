//! @note Missing file header.

//! @note <cstdio> not used here.
#include <cstdio>

#include "system/pin_manager/esp32s3.h"
#include "test/pin_manager.h"

//! @note Missing doc of main.
int main()
{
    auto& pinManager = sys::pin_manager::Esp32s3::instance();

    //! @note Tip: Return 0 on success and -1 on failure like this:
    //! return test::runPinManagerTest(pinManager) ? 0 : -1;
    if (!test::runPinManagerTest(pinManager)) { return -1; }
    return 0;
}