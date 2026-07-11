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
    unit/application_runtime_test.cpp
    unit/sim_control_server_test.cpp
    unit/recipe_parser_test.cpp
    unit/ota_updater_test.cpp
    unit/heater_pid_test.cpp
    unit/parse_number_test.cpp
    unit/motor_controller_test.cpp)
target_link_libraries(unit_tests PRIVATE culina_system GTest::gtest_main)
culina_set_warnings(unit_tests)
gtest_discover_tests(unit_tests DISCOVERY_MODE PRE_TEST PROPERTIES LABELS unit)

add_executable(integration_tests integration/mcu_link_test.cpp integration/mcu_client_test.cpp
               integration/cooking_test.cpp integration/guided_recipe_test.cpp
               integration/commands_test.cpp)
target_include_directories(integration_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(integration_tests PRIVATE culina_cli GTest::gtest_main)
culina_set_warnings(integration_tests)
gtest_discover_tests(integration_tests DISCOVERY_MODE PRE_TEST PROPERTIES LABELS integration)

add_executable(perf_check perf/perf_check.cpp)
target_link_libraries(perf_check PRIVATE culina_system)
culina_set_warnings(perf_check)

add_executable(scenario_tests integration/scenario_check_test.cpp)
target_compile_definitions(scenario_tests PRIVATE CULINA_DATA_DIR="${CMAKE_SOURCE_DIR}/data")
target_link_libraries(scenario_tests PRIVATE culina_cli GTest::gtest_main)
culina_set_warnings(scenario_tests)
gtest_discover_tests(scenario_tests DISCOVERY_MODE PRE_TEST PROPERTIES LABELS scenario)

add_test(NAME C1LinkDump.ValidCapture
         COMMAND c1link_dump ${CMAKE_SOURCE_DIR}/data/captures/startup.hex)
set_tests_properties(C1LinkDump.ValidCapture PROPERTIES LABELS tool)

add_test(NAME C1LinkDump.RejectsTruncatedCapture
         COMMAND c1link_dump ${CMAKE_SOURCE_DIR}/data/captures/truncated.hex)
set_tests_properties(C1LinkDump.RejectsTruncatedCapture PROPERTIES LABELS tool WILL_FAIL TRUE)

add_test(NAME C1LinkDump.RejectsBadCrc
         COMMAND c1link_dump ${CMAKE_SOURCE_DIR}/data/captures/bad-crc.hex)
set_tests_properties(C1LinkDump.RejectsBadCrc PROPERTIES LABELS tool WILL_FAIL TRUE)

add_test(NAME TwoProcess.SafeCommandLifecycle
         COMMAND sh ${CMAKE_CURRENT_SOURCE_DIR}/two_process_smoke.sh
                 $<TARGET_FILE:culina_mcu> $<TARGET_FILE:culina_app>)
set_tests_properties(TwoProcess.SafeCommandLifecycle PROPERTIES LABELS integration TIMEOUT 15)

add_test(NAME TwoProcess.DetectsDisconnect
         COMMAND sh ${CMAKE_CURRENT_SOURCE_DIR}/two_process_disconnect.sh
                 $<TARGET_FILE:culina_mcu> $<TARGET_FILE:culina_app>)
set_tests_properties(TwoProcess.DetectsDisconnect PROPERTIES LABELS integration TIMEOUT 10)

add_test(NAME TwoProcess.RejectsInvalidWater COMMAND culina_mcu --water nan)
set_tests_properties(TwoProcess.RejectsInvalidWater PROPERTIES LABELS integration WILL_FAIL TRUE)

add_test(NAME TwoProcess.RejectsInvalidSocketPath COMMAND culina_mcu --socket /dev/null/c1link)
set_tests_properties(TwoProcess.RejectsInvalidSocketPath PROPERTIES LABELS integration WILL_FAIL TRUE)
