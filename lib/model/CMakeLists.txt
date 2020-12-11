project(image-processor-model)

#add_library(${PROJECT_NAME})

add_library(image-processor::view
        ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
        PUBLIC sdl2 glad2-loader)

target_include_directories(${PROJECT_NAME}
        PUBLIC .)
