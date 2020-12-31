#ifndef IMAGEPROCESSOR_GL_MEDIAN_SHADER_PROGRAM_H
#define IMAGEPROCESSOR_GL_MEDIAN_SHADER_PROGRAM_H

#include <filesystem>

#include "gl_shader_program.h"

namespace image_processor::model::shader_programs {

class GlMedianShaderProgram final : public GlShaderProgram {
  public:
    using Path = std::filesystem::path;

    GlMedianShaderProgram(unsigned int kernel_half_size_x, unsigned int kernel_half_size_y);

    auto GetPositionsAttribute() const -> GLuint { return positions_attribute_; }
    auto GetTextureCoordinateAttribute() const -> GLuint { return texture_coordinates_attribute_; }

    auto GetImageUniform() const -> GLuint { return image_uniform_; }

  private:
    static auto InjectParameters(const Path& path, unsigned int kernel_half_size_x,
                                 unsigned int kernel_half_size_y) -> std::string;

    GLuint positions_attribute_;
    GLuint texture_coordinates_attribute_;

    GLuint kernel_half_size_uniform_;
    GLuint image_uniform_;
};

}  // namespace image_processor::model::shader_programs

#endif  // IMAGEPROCESSOR_GL_MEDIAN_SHADER_PROGRAM_H
