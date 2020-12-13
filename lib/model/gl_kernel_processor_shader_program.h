#ifndef IMAGEPROCESSOR_GL_KERNEL_PROCESSOR_SHADER_PROGRAM_H
#define IMAGEPROCESSOR_GL_KERNEL_PROCESSOR_SHADER_PROGRAM_H

#include <gl_shader.h>
#include <glad/gl.h>

#include <filesystem>

namespace image_processor::model {

class GlKernelProcessorShaderProgram final {
  public:
    using Path = std::filesystem::path;
    GlKernelProcessorShaderProgram(const Path& vertex_shader_path,
                                   const Path& fragment_shader_path);
    GlKernelProcessorShaderProgram(GlKernelProcessorShaderProgram&& other) noexcept;
    GlKernelProcessorShaderProgram& operator=(GlKernelProcessorShaderProgram&& other);
    ~GlKernelProcessorShaderProgram();

    auto GetPositionsAttribute() const -> GLuint { return positions_attribute_; }
    auto GetTextureCoordinateAttribute() const -> GLuint { return texture_coordinates_attribute_; }

    auto GetKernelUniform() const -> GLuint { return kernel_uniform_; }
    auto GetImageUniform() const -> GLuint { return image_uniform_; }

    auto GetID() const -> GLuint { return program_id_; }

  private:
    GlKernelProcessorShaderProgram(const GlKernelProcessorShaderProgram& other) = default;
    GlKernelProcessorShaderProgram& operator=(const GlKernelProcessorShaderProgram& other) =
        default;

    GlShader vertex_shader_;
    GlShader fragment_shader_;

    GLuint positions_attribute_;
    GLuint texture_coordinates_attribute_;

    GLuint kernel_uniform_;
    GLuint image_uniform_;

    GLuint program_id_;
};

}  // namespace image_processor::model

#endif  // IMAGEPROCESSOR_GL_KERNEL_PROCESSOR_SHADER_PROGRAM_H
