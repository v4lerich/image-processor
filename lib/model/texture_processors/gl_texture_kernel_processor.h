#ifndef IMAGEPROCESSOR_GL_TEXTURE_KERNEL_PROCESSOR_H
#define IMAGEPROCESSOR_GL_TEXTURE_KERNEL_PROCESSOR_H

#include <gl_texture.h>
#include <kernel.h>

#include "gl_texture_processor.h"
#include "shader_programs/gl_kernel_based_shader_program.h"

namespace image_processor::model::texture_processors {

class GlTextureKernelProcessor : public GlTextureProcessor {
  public:
    GlTextureKernelProcessor(const shader_programs::GlKernelBasedShaderProgram& program, const Kernel& kernel);

  protected:
    void PrepareProcessing(const GlTexture& texture) override;

  private:
    static auto CreateKernelGlTexture(const Kernel& kernel) -> GlTexture;

    GlTexture kernel_texture_;
    const shader_programs::GlKernelBasedShaderProgram& program_;
    const Kernel& kernel_;
};

}  // namespace image_processor::model::texture_processors

#endif  // IMAGEPROCESSOR_GL_TEXTURE_KERNEL_PROCESSOR_H
