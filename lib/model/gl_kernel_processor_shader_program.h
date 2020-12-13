#ifndef IMAGEPROCESSOR_GL_KERNEL_PROCESSOR_SHADER_PROGRAM_H
#define IMAGEPROCESSOR_GL_KERNEL_PROCESSOR_SHADER_PROGRAM_H

#include <filesystem>
#include <glad/gl.h>

namespace image_processor::model {

class GlKernelProcessorShaderProgram final {
  public:
    using Path = std::filesystem::path;
    GlKernelProcessorShaderProgram(const Path& vertex_shader_path, const Path& fragment_shader_path);
    ~GlKernelProcessorShaderProgram();

  private:

    class GlShader final {
      public:
        GlShader(const Path& path);


      private:
        GLuint id_;
    };

    GLuint vertex_shader_;
    Gluint fragment_shader_;
};

}  // namespace image_processor::model

#endif  // IMAGEPROCESSOR_GL_KERNEL_PROCESSOR_SHADER_PROGRAM_H
