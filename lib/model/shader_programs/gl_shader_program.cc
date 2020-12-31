#include "gl_shader_program.h"

namespace image_processor::model::shader_programs {

GlShaderProgram::GlShaderProgram(std::initializer_list<GlShader> shaders)
    : GlShaderProgram(shaders.begin(), shaders.end()) {}

void GlShaderProgram::DeleteShaderProgram(GLuint* program_id) {
    if (*program_id != 0) glDeleteProgram(*program_id);
}

}  // namespace image_processor::model::shader_programs
