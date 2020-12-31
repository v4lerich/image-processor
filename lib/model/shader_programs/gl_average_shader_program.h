#ifndef IMAGEPROCESSOR_GL_AVERAGE_SHADER_PROGRAM_H
#define IMAGEPROCESSOR_GL_AVERAGE_SHADER_PROGRAM_H

#include "gl_shader_program.h"

namespace image_processor::model::shader_programs {

class GlAverageShaderProgram final : public GlShaderProgram {
  public:
    GlAverageShaderProgram();

    auto GetPositionsAttribute() const -> GLuint { return positions_attribute_; }
    auto GetTextureCoordinateAttribute() const -> GLuint { return texture_coordinates_attribute_; }

    auto GetKernelHalfSizeUniform() const -> GLuint { return kernel_half_size_uniform_; }
    auto GetImageUniform() const -> GLuint { return image_uniform_; }

  private:
    GLuint positions_attribute_;
    GLuint texture_coordinates_attribute_;

    GLuint kernel_half_size_uniform_;
    GLuint image_uniform_;
};

}  // namespace image_processor::model::shader_programs

#endif  // IMAGEPROCESSOR_GL_AVERAGE_SHADER_PROGRAM_H
