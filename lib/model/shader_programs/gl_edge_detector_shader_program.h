#ifndef IMAGEPROCESSOR_GL_EDGE_DETECTOR_SHADER_PROGRAM_H
#define IMAGEPROCESSOR_GL_EDGE_DETECTOR_SHADER_PROGRAM_H

#include "gl_shader_program.h"

namespace image_processor::model::shader_programs {

class GlEdgeDetectorShaderProgram final : public GlShaderProgram {
  public:
    GlEdgeDetectorShaderProgram();

    auto GetPositionsAttribute() const -> GLuint { return positions_attribute_; }
    auto GetTextureCoordinateAttribute() const -> GLuint { return texture_coordinates_attribute_; }

    auto GetXKernelUniform() const -> GLuint { return x_kernel_uniform_; }
    auto GetYKernelUniform() const -> GLuint { return y_kernel_uniform_; }
    auto GetImageUniform() const -> GLuint { return image_uniform_; }

  private:
    GLuint positions_attribute_;
    GLuint texture_coordinates_attribute_;

    GLuint image_uniform_;
    GLuint x_kernel_uniform_;
    GLuint y_kernel_uniform_;
};

}  // namespace image_processor::model::shader_programs

#endif  // IMAGEPROCESSOR_GL_EDGE_DETECTOR_SHADER_PROGRAM_H
