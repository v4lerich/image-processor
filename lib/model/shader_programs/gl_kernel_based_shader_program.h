#ifndef IMAGEPROCESSOR_GL_KERNEL_BASED_SHADER_PROGRAM_H
#define IMAGEPROCESSOR_GL_KERNEL_BASED_SHADER_PROGRAM_H

#include <gl_shader.h>
#include <glad/gl.h>

#include <filesystem>

#include "gl_shader_program.h"

namespace image_processor::model::shader_programs {

class GlKernelBasedShaderProgram final : public GlShaderProgram {
  public:
    GlKernelBasedShaderProgram();
    GlKernelBasedShaderProgram(GlKernelBasedShaderProgram&& other) noexcept;
    GlKernelBasedShaderProgram& operator=(GlKernelBasedShaderProgram&& other);
    ~GlKernelBasedShaderProgram() override;

    auto GetPositionsAttribute() const -> GLuint { return positions_attribute_; }
    auto GetTextureCoordinateAttribute() const -> GLuint { return texture_coordinates_attribute_; }

    auto GetKernelUniform() const -> GLuint { return kernel_uniform_; }
    auto GetImageUniform() const -> GLuint { return image_uniform_; }

  private:
    GlKernelBasedShaderProgram(const GlKernelBasedShaderProgram& other) = default;
    GlKernelBasedShaderProgram& operator=(const GlKernelBasedShaderProgram& other) =
        default;

    GLuint positions_attribute_;
    GLuint texture_coordinates_attribute_;

    GLuint kernel_uniform_;
    GLuint image_uniform_;
};

}  // namespace image_processor::model::shader_programs

#endif  // IMAGEPROCESSOR_GL_KERNEL_BASED_SHADER_PROGRAM_H
