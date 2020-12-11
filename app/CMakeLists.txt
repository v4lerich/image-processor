project(image-processor)

add_executable(${PROJECT_NAME}
        application.h application.cc
        main.cc)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        imgui
        sdl2
        glad2-loader
        image-processor::view
        image-processor::model
        icon-font-headers)

install(TARGETS ${PROJECT_NAME}
        DESTINATION bin)