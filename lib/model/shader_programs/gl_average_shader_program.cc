#include "gl_average_shader_program.h"

namespace image_processor::model::shader_programs {

static const std::filesystem::path kVertexShaderPath =
    std::filesystem::path{std::string{"./res/shaders/common.vert"}};
static const std::filesystem::path kFragmentShaderPath =
    std::filesystem::path{std::string{"./res/shaders/average.frag"}};

GlAverageShaderProgram::GlAverageShaderProgram()
    : GlShaderProgram{{GlShader{GL_VERTEX_SHADER, kVertexShaderPath},
                       GlShader{GL_FRAGMENT_SHADER, kFragmentShaderPath}}} {
    positions_attribute_ = glGetAttribLocation(GetID(), "position");
    texture_coordinates_attribute_ = glGetAttribLocation(GetID(), "texture_coordinate");

    kernel_half_size_uniform_ = glGetUniformLocation(GetID(), "kernel_half_size");
    image_uniform_ = glGetUniformLocation(GetID(), "image");
}

GlAverageShaderProgram::~GlAverageShaderProgram() = default;

GlAverageShaderProgram::GlAverageShaderProgram(GlAverageShaderProgram&& other) noexcept
    : GlShaderProgram{std::move(other)} {
    positions_attribute_ = other.positions_attribute_;
    texture_coordinates_attribute_ = other.texture_coordinates_attribute_;

    kernel_half_size_uniform_ = other.kernel_half_size_uniform_;
    image_uniform_ = other.image_uniform_;
}

GlAverageShaderProgram& GlAverageShaderProgram::operator=(GlAverageShaderProgram&& other) {
    positions_attribute_ = other.positions_attribute_;
    texture_coordinates_attribute_ = other.texture_coordinates_attribute_;

    kernel_half_size_uniform_ = other.kernel_half_size_uniform_;
    image_uniform_ = other.image_uniform_;
    *this = std::move(other);
    return *this;
}

}  // namespace image_processor::model::shader_programs
