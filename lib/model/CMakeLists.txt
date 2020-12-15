project(image-processor-model)

add_library(${PROJECT_NAME}
        image_processor_model.h image_processor_model.cc
        shader_programs/gl_shader_program.h shader_programs/gl_shader_program.cc
        shader_programs/gl_kernel_based_shader_program.h shader_programs/gl_kernel_based_shader_program.cc
        shader_programs/gl_average_shader_program.h shader_programs/gl_average_shader_program.cc
        shader_programs/gl_edge_detector_shader_program.h shader_programs/gl_edge_detector_shader_program.cc
        shader_programs/gl_edge_detector_shader_program.h shader_programs/gl_edge_detector_shader_program.cc
        texture_processors/gl_texture_processor.h texture_processors/gl_texture_processor.cc
        texture_processors/gl_texture_kernel_processor.h texture_processors/gl_texture_kernel_processor.cc
        texture_processors/gl_texture_average_processor.h texture_processors/gl_texture_average_processor.cc
        texture_processors/gl_texture_edge_detector_processor.h texture_processors/gl_texture_edge_detector_processor.cc
        gl_texture.h gl_texture.cc
        gl_shader.h gl_shader.cc
        kernel.h kernel.cc)

add_library(image-processor::model
        ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
        PUBLIC glad2-loader)

target_include_directories(${PROJECT_NAME}
        PUBLIC .)
