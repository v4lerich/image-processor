project(glad2-loader)

if (TARGET ${PROJECT_NAME})
    return()
endif()

add_subdirectory(glad/cmake)
glad_add_library(glad_gl_core_42
        REPRODUCIBLE STATIC ALIAS
        LANGUAGE "c++"
        API gl:core=4.2)

find_package(SDL2 REQUIRED)
add_library(${PROJECT_NAME}
        glad2_loader.h glad2_loader.cc)

target_link_libraries(${PROJECT_NAME}
        PRIVATE ${SDL2_LIBRARY}
        PUBLIC glad_gl_core_42)

target_include_directories(${PROJECT_NAME}
        PUBLIC . ${SDL2_INCLUDE_DIR})
