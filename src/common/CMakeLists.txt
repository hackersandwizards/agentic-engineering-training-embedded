add_library(culina_common STATIC crc16.cpp logging.cpp)
target_include_directories(culina_common PUBLIC ${CMAKE_SOURCE_DIR}/src)
culina_firmware_target(culina_common)
