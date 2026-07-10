add_library(
    culina_mcu_lib STATIC
    safety_mcu.cpp
    interlocks.cpp
    motor_controller.cpp
    heater_pid.cpp
    command_handler.cpp
    telemetry_publisher.cpp)
target_link_libraries(culina_mcu_lib PUBLIC culina_protocol)
culina_firmware_target(culina_mcu_lib)
