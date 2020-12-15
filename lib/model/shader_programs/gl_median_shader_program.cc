#include "gl_median_shader_program.h"

#include <vector>

namespace image_processor::model::shader_programs {

static const std::filesystem::path kVertexShaderPath =
    std::filesystem::path{std::string{"./res/shaders/common.vert"}};
static const std::filesystem::path kFragmentShaderPath =
    std::filesystem::path{std::string{"./res/shaders/median.frag"}};

GlMedianShaderProgram::GlMedianShaderProgram(unsigned int kernel_half_size_x,
                                             unsigned int kernel_half_size_y)
    : GlShaderProgram{
          {GlShader{GL_VERTEX_SHADER, kVertexShaderPath},
           GlShader{GL_FRAGMENT_SHADER, InjectParameters(kFragmentShaderPath, kernel_half_size_x,
                                                         kernel_half_size_y)}}} {
    positions_attribute_ = glGetAttribLocation(GetID(), "position");
    texture_coordinates_attribute_ = glGetAttribLocation(GetID(), "texture_coordinate");

    image_uniform_ = glGetUniformLocation(GetID(), "image");
}

GlMedianShaderProgram::~GlMedianShaderProgram() = default;

GlMedianShaderProgram::GlMedianShaderProgram(GlMedianShaderProgram&& other) noexcept
    : GlShaderProgram{std::move(other)} {
    positions_attribute_ = other.positions_attribute_;
    texture_coordinates_attribute_ = other.texture_coordinates_attribute_;

    kernel_half_size_uniform_ = other.kernel_half_size_uniform_;
    image_uniform_ = other.image_uniform_;
}

GlMedianShaderProgram& GlMedianShaderProgram::operator=(GlMedianShaderProgram&& other) {
    positions_attribute_ = other.positions_attribute_;
    texture_coordinates_attribute_ = other.texture_coordinates_attribute_;

    kernel_half_size_uniform_ = other.kernel_half_size_uniform_;
    image_uniform_ = other.image_uniform_;
    *this = std::move(other);
    return *this;
}
auto GlMedianShaderProgram::InjectParameters(const Path& path, unsigned int kernel_half_size_x,
                                             unsigned int kernel_half_size_y) -> std::string {
    auto source = GlShader::LoadShader(path);

    std::vector<std::string> lines{};
    std::stringstream source_stream{source};

    for (std::string line; std::getline(source_stream, line);) {
        lines.push_back(std::move(line));
    }

    lines.insert(std::next(lines.begin()),
                 {
                     "#define KERNEL_HALF_SIZE_X " + std::to_string(kernel_half_size_x),
                     "#define KERNEL_HALF_SIZE_Y " + std::to_string(kernel_half_size_y),
                 });

    std::string injected_source{};
    for (auto& line : lines) {
        injected_source += std::move(line);
        injected_source += '\n';
    }
    return injected_source;
}

}  // namespace image_processor::model::shader_programs
