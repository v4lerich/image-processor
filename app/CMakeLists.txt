project(image-processor)

add_executable(${PROJECT_NAME}
        application.h application.cc
        main.cc)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        imgui
        glad2-loader
        sdl2
        image-processor::view
        icon-font-headers)

install(TARGETS ${PROJECT_NAME}
        DESTINATION bin)