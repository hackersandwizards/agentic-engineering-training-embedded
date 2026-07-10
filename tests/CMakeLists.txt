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
    unit/link_test.cpp)
target_link_libraries(unit_tests PRIVATE culina_sim culina_protocol GTest::gtest_main)
culina_set_warnings(unit_tests)
gtest_discover_tests(unit_tests PROPERTIES LABELS unit)

add_executable(integration_tests integration/mcu_link_test.cpp)
target_include_directories(integration_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(integration_tests PRIVATE culina_sim culina_mcu_lib GTest::gtest_main)
culina_set_warnings(integration_tests)
gtest_discover_tests(integration_tests PROPERTIES LABELS integration)
