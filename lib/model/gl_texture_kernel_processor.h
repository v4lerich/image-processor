#ifndef IMAGEPROCESSOR_GL_TEXTURE_KERNEL_PROCESSOR_H
#define IMAGEPROCESSOR_GL_TEXTURE_KERNEL_PROCESSOR_H

#include <gl_texture.h>
#include <kernel.h>
#include <gl_kernel_processor_shader_program.h>

namespace image_processor::model {

class GlTextureKernelProcessor final {
  public:
    explicit GlTextureKernelProcessor(const GlKernelProcessorShaderProgram& program, const Kernel& kernel);

    auto Process(const GlTexture& texture) -> GlTexture;

  private:
    static auto CreateKernelGlTexture(const Kernel& kernel) -> GlTexture;
    static auto CreateProcessingTexture(const GlTexture& texture) -> GlTexture;
    static auto CreateProcessingFramebuffer(const GlTexture& rendered_texture) -> GLuint;
    void CreateTextureBoxVao(const GlTexture& texture);
    void CreateTextureBoxIndexVbo();

    GLuint vao_id_;
    GLuint positions_vbo_id_;
    GLuint texture_cooordinates_vbo_id_;
    GLuint indices_vbo_id_;

    GlTexture kernel_texture_;
    const GlKernelProcessorShaderProgram& program_;
    const Kernel& kernel_;
};

}  // namespace image_processor::model

#endif  // IMAGEPROCESSOR_GL_TEXTURE_KERNEL_PROCESSOR_H
