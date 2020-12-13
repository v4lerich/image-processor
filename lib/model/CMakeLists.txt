project(image-processor-model)

add_library(${PROJECT_NAME}
        image_processor_model.h image_processor_model.cc
        gl_texture_kernel_processor.h gl_texture_kernel_processor.cc
        gl_texture.h gl_texture.cc
        kernel.h kernel.cc)

add_library(image-processor::model
        ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
        PUBLIC glad2-loader)

target_include_directories(${PROJECT_NAME}
        PUBLIC .)
