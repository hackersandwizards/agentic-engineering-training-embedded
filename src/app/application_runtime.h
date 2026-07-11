#pragma once

#include "app/cooking/cooking_controller.h"
#include "app/mcu_client.h"
#include "app/ota/ota_updater.h"
#include "app/recipe/recipe_library.h"
#include "app/telemetry_store.h"

namespace culina::app {

class ApplicationRuntime {
public:
    ApplicationRuntime(hal::IUart* uart, const hal::IClock* clock, hal::IWatchdog* watchdog);

    void tick_1ms();

    TelemetryStore& telemetry() { return telemetry_; }
    const TelemetryStore& telemetry() const { return telemetry_; }
    McuClient& client() { return client_; }
    const McuClient& client() const { return client_; }
    CookingController& controller() { return controller_; }
    const CookingController& controller() const { return controller_; }
    RecipeLibrary& recipes() { return recipes_; }
    const RecipeLibrary& recipes() const { return recipes_; }
    OtaUpdater& ota() { return ota_; }
    const OtaUpdater& ota() const { return ota_; }

private:
    TelemetryStore telemetry_;
    McuClient client_;
    CookingController controller_;
    RecipeLibrary recipes_;
    OtaUpdater ota_;
    std::uint8_t app_divider_ = 0;
};

} // namespace culina::app
