add_library(culina_hal INTERFACE)
target_include_directories(culina_hal INTERFACE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(culina_hal INTERFACE culina_common)
