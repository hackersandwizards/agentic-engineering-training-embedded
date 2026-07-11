cmake_minimum_required(VERSION 3.24)

project(culina VERSION 0.9.0 LANGUAGES CXX)

option(CULINA_BUILD_UI "Build the Qt touchscreen simulator" OFF)

if(CULINA_BUILD_UI)
    find_package(Qt6 6.5 REQUIRED COMPONENTS Quick QuickControls2 Qml Network)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(CompilerWarnings)
include(Sanitizers)

add_subdirectory(src)
add_subdirectory(apps)
add_subdirectory(tools)

include(CTest)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
