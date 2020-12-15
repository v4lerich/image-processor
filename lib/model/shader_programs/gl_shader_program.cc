#include "gl_shader_program.h"

namespace image_processor::model::shader_programs {

GlShaderProgram::GlShaderProgram(std::initializer_list<GlShader> shaders)
    : GlShaderProgram(shaders.begin(), shaders.end()) {}

GlShaderProgram::GlShaderProgram(GlShaderProgram&& other) noexcept
    : program_id_{other.program_id_} {
    other.program_id_ = 0;
}

GlShaderProgram& GlShaderProgram::operator=(GlShaderProgram&& other) {
    program_id_ = other.program_id_;
    other.program_id_ = 0;
    return *this;
}

GlShaderProgram::~GlShaderProgram() {
    if (program_id_ != 0) {
        glDeleteProgram(program_id_);
    }
}

}  // namespace image_processor::model::shader_programs
