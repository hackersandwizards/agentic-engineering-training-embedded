include(FetchGoogleTest)
include(GoogleTest)

add_executable(
    unit_tests
    unit/ring_buffer_test.cpp
    unit/crc16_test.cpp
    unit/result_test.cpp
    unit/sim_models_test.cpp
    unit/sim_board_test.cpp
    unit/frame_parser_test.cpp
    unit/link_test.cpp
    unit/telemetry_store_test.cpp
    unit/recipe_parser_test.cpp
    unit/ota_updater_test.cpp
    unit/heater_pid_test.cpp)
target_link_libraries(unit_tests PRIVATE culina_simulation culina_protocol culina_app_lib
                                         culina_mcu_lib GTest::gtest_main)
culina_set_warnings(unit_tests)
gtest_discover_tests(unit_tests PROPERTIES LABELS unit)

add_executable(integration_tests integration/mcu_link_test.cpp integration/mcu_client_test.cpp
               integration/cooking_test.cpp integration/guided_recipe_test.cpp)
target_include_directories(integration_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(integration_tests PRIVATE culina_simulation culina_mcu_lib culina_app_lib GTest::gtest_main)
culina_set_warnings(integration_tests)
gtest_discover_tests(integration_tests PROPERTIES LABELS integration)

add_executable(scenario_tests integration/scenario_check_test.cpp)
target_compile_definitions(scenario_tests PRIVATE CULINA_DATA_DIR="${CMAKE_SOURCE_DIR}/data")
target_link_libraries(scenario_tests PRIVATE culina_cli GTest::gtest_main)
culina_set_warnings(scenario_tests)
gtest_discover_tests(scenario_tests PROPERTIES LABELS scenario)
