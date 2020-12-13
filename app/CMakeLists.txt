project(image-processor)

add_executable(${PROJECT_NAME}
        application.h application.cc
        main.cc)

find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        imgui
        ${SDL2_LIBRARIES}
        glad2-loader
        image-processor::view
        image-processor::model
        icon-font-headers)

install(TARGETS ${PROJECT_NAME}
        DESTINATION bin)

add_dependencies(${PROJECT_NAME}
        image-processor-resources
        fork-awesome)