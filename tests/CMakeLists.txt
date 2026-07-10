include(FetchGoogleTest)
include(GoogleTest)

add_executable(unit_tests unit/ring_buffer_test.cpp unit/crc16_test.cpp unit/result_test.cpp)
target_link_libraries(unit_tests PRIVATE culina_common GTest::gtest_main)
culina_set_warnings(unit_tests)
gtest_discover_tests(unit_tests PROPERTIES LABELS unit)
