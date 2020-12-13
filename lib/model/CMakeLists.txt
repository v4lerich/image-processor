project(image-processor-model)

add_library(${PROJECT_NAME}
        image_processor_model.h image_processor_model.cc
        kernel.h kernel.cc)

add_library(image-processor::model
        ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
        PUBLIC glad2-loader)

target_include_directories(${PROJECT_NAME}
        PUBLIC .)
