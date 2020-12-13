#include "gl_kernel_processor_shader_program.h"

namespace image_processor::model {

GlKernelProcessorShaderProgram::GlKernelProcessorShaderProgram(const Path& vertex_shader_path,
                                                               const Path& fragment_shader_path) {}

GlKernelProcessorShaderProgram::~GlKernelProcessorShaderProgram() {
    if (vertex_shader_ != 0) {
        glDeleteShader(vertex_shader_);
    }
    if (!= 0) {
        glDeleteShader(vertex_shader_);
    }
}

}  // namespace image_processor::model
