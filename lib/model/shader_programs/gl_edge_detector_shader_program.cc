#include "gl_edge_detector_shader_program.h"

namespace image_processor::model::shader_programs {

static const std::filesystem::path kVertexShaderPath =
    std::filesystem::path{std::string{"./res/shaders/common.vert"}};
static const std::filesystem::path kFragmentShaderPath =
    std::filesystem::path{std::string{"./res/shaders/edge_detector.frag"}};

GlEdgeDetectorShaderProgram::GlEdgeDetectorShaderProgram()
    : GlShaderProgram{{GlShader{GL_VERTEX_SHADER, kVertexShaderPath},
                       GlShader{GL_FRAGMENT_SHADER, kFragmentShaderPath}}} {
    positions_attribute_ = glGetAttribLocation(GetID(), "position");
    texture_coordinates_attribute_ = glGetAttribLocation(GetID(), "texture_coordinate");

    image_uniform_ = glGetUniformLocation(GetID(), "image");
    x_kernel_uniform_ = glGetUniformLocation(GetID(), "x_kernel");
    y_kernel_uniform_ = glGetUniformLocation(GetID(), "y_kernel");
}

GlEdgeDetectorShaderProgram::~GlEdgeDetectorShaderProgram() = default;

GlEdgeDetectorShaderProgram::GlEdgeDetectorShaderProgram(
    GlEdgeDetectorShaderProgram&& other) noexcept
    : GlShaderProgram{std::move(other)} {
    positions_attribute_ = other.positions_attribute_;
    texture_coordinates_attribute_ = other.texture_coordinates_attribute_;

    image_uniform_ = other.image_uniform_;
    x_kernel_uniform_ = other.x_kernel_uniform_;
    y_kernel_uniform_ = other.y_kernel_uniform_;
}

GlEdgeDetectorShaderProgram& GlEdgeDetectorShaderProgram::operator=(
    GlEdgeDetectorShaderProgram&& other) {
    positions_attribute_ = other.positions_attribute_;
    texture_coordinates_attribute_ = other.texture_coordinates_attribute_;

    image_uniform_ = other.image_uniform_;
    x_kernel_uniform_ = other.x_kernel_uniform_;
    y_kernel_uniform_ = other.y_kernel_uniform_;
    *this = std::move(other);
    return *this;
}

}  // namespace image_processor::model::shader_programs
