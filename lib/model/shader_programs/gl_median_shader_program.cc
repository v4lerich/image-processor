#include "gl_median_shader_program.h"

#include <vector>

namespace image_processor::model::shader_programs {

static const std::filesystem::path kVertexShaderPath =
    std::filesystem::path{std::string{"./res/shaders/common.vert"}};
static const std::filesystem::path kFragmentShaderPath =
    std::filesystem::path{std::string{"./res/shaders/median.frag"}};

GlMedianShaderProgram::GlMedianShaderProgram()
    : GlShaderProgram{{GlShader(GL_VERTEX_SHADER, kVertexShaderPath),
                       GlShader(GL_FRAGMENT_SHADER, kFragmentShaderPath)}} {
    positions_attribute_ = glGetAttribLocation(GetID(), "position");
    texture_coordinates_attribute_ = glGetAttribLocation(GetID(), "texture_coordinate");

    kernel_half_size_uniform_ = glGetUniformLocation(GetID(), "kernel_half_size");
    image_uniform_ = glGetUniformLocation(GetID(), "image");
}

}  // namespace image_processor::model::shader_programs
