#include "gl_kernel_processor_shader_program.h"

namespace image_processor::model {

GlKernelProcessorShaderProgram::GlKernelProcessorShaderProgram(const Path& vertex_shader_path,
                                                               const Path& fragment_shader_path)
    : vertex_shader_{GL_VERTEX_SHADER, vertex_shader_path},
      fragment_shader_{GL_FRAGMENT_SHADER, fragment_shader_path} {
    program_id_ = glCreateProgram();
    glAttachShader(program_id_, vertex_shader_.GetID());
    glAttachShader(program_id_, fragment_shader_.GetID());

    glLinkProgram(program_id_);
    GLint link_status;
    glGetProgramiv(program_id_, GL_LINK_STATUS, &link_status);

    if (link_status != GL_TRUE) {
        int info_log_length;
        glGetProgramiv(program_id_, GL_INFO_LOG_LENGTH, &info_log_length);

        std::string info_log;
        info_log.resize(info_log_length);
        glGetProgramInfoLog(program_id_, info_log_length, nullptr, info_log.data());

        glDeleteShader(program_id_);
        throw std::runtime_error("Program link error: " + info_log);
    }

    positions_attribute_ = glGetAttribLocation(program_id_, "position");
    texture_coordinates_attribute_ = glGetAttribLocation(program_id_, "texture_coordinate");

    kernel_uniform_ = glGetUniformLocation(program_id_, "kernel");
    image_uniform_ = glGetUniformLocation(program_id_, "image");
}

GlKernelProcessorShaderProgram::~GlKernelProcessorShaderProgram() {
    if (program_id_ != 0) {
        glDeleteProgram(program_id_);
    }
}

GlKernelProcessorShaderProgram::GlKernelProcessorShaderProgram(
    GlKernelProcessorShaderProgram&& other) noexcept
    : fragment_shader_{std::move(other.fragment_shader_)},
      vertex_shader_{std::move(other.vertex_shader_)},
      program_id_{other.program_id_} {
    other.program_id_ = 0;
}

GlKernelProcessorShaderProgram& GlKernelProcessorShaderProgram::operator=(
    GlKernelProcessorShaderProgram&& other) {
    fragment_shader_ = std::move(other.fragment_shader_);
    vertex_shader_ = std::move(other.vertex_shader_);
    program_id_ = other.program_id_;
    other.program_id_ = 0;
    return *this;
}

}  // namespace image_processor::model
