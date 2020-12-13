#ifndef IMAGEPROCESSOR_GL_TEXTURE_KERNEL_PROCESSOR_H
#define IMAGEPROCESSOR_GL_TEXTURE_KERNEL_PROCESSOR_H

#include <gl_texture.h>
#include <kernel.h>

namespace image_processor::model {

class GlImageKernelProcessor final {
  public:
    explicit GlImageKernelProcessor(const Kernel& kernel);

    auto Process(const GlTexture& texture) -> GlTexture;

  private:
    static auto CreateKernelGlTexture(const Kernel& kernel) -> GlTexture;
    static auto CreateProcessingTexture(const GlTexture& texture) -> GlTexture;
    static auto CreateProcessingFramebuffer(const GlTexture& rendered_texture) -> GLuint;
    static auto CreateTextureBoxVao(const GlTexture& texture) -> GLuint;

    GlTexture kernel_texture_;
    const Kernel& kernel_;
};

}  // namespace image_processor::model

#endif  // IMAGEPROCESSOR_GL_TEXTURE_KERNEL_PROCESSOR_H
