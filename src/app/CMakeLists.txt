add_library(
    culina_app_lib STATIC
    telemetry_store.cpp
    mcu_client.cpp
    cooking/cooking_controller.cpp
    cooking/manual_mode.cpp
    cooking/dough_mode.cpp
    cooking/steam_mode.cpp
    cooking/sous_vide_mode.cpp
    cooking/turbo_pulse.cpp)
target_link_libraries(culina_app_lib PUBLIC culina_protocol culina_hal culina_common)
culina_set_warnings(culina_app_lib)
