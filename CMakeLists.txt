cmake_minimum_required(VERSION 3.15)
set(CMAKE_VERBOSE_MAKEFILE OFF)
project(ImageProcessor
        VERSION 1.1
        LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message("Setting build type to 'RelWithDebInfo' as none was specified.")
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)

    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
            "Debug" "Release"
            "MinSizeRel" "RelWithDebInfo")
endif()

set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/sdl2/sdl2-cmake-modules)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(RESOURCE_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res")

add_subdirectory(3rd_party/)
add_subdirectory(app/)
add_subdirectory(lib/)
add_subdirectory(res/)
