#include "app/application_runtime.h"

namespace culina::app {

ApplicationRuntime::ApplicationRuntime(hal::IUart* uart, const hal::IClock* clock,
                                       hal::IWatchdog* watchdog)
    : client_(uart, clock, &telemetry_), controller_(&client_, &telemetry_, clock, watchdog) {
    controller_.attach_ota(&ota_);
}

void ApplicationRuntime::tick_1ms() {
    client_.poll();
    if (++app_divider_ >= 10) {
        app_divider_ = 0;
        controller_.tick_10ms();
    }
}

} // namespace culina::app
