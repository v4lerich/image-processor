#ifndef IMAGEPROCESSOR_GL_TEXTURE_PROCESSOR_H
#define IMAGEPROCESSOR_GL_TEXTURE_PROCESSOR_H

#include <gl_texture.h>
#include <kernel.h>

#include "shader_programs/gl_kernel_based_shader_program.h"

namespace image_processor::model::texture_processors {

class GlTextureProcessor {
  public:
    GlTextureProcessor();

    auto Process(const GlTexture& texture) -> GlTexture;

  protected:
    virtual void PrepareProcessing(const GlTexture& texture);
    auto GetPositionsVbo() const -> GLuint { return positions_vbo_id_; }
    auto GetTextureCoordinatesVbo() const -> GLuint { return texture_cooordinates_vbo_id_; }

    static auto CreateKernelGlTexture(const Kernel& kernel) -> GlTexture;

  private:
    static auto CreateProcessingTexture(const GlTexture& texture) -> GlTexture;
    static auto CreateProcessingFramebuffer(const GlTexture& rendered_texture) -> GLuint;
    void CreateTextureBoxVao(const GlTexture& texture);
    void CreateTextureBoxIndexVbo();

    GLuint vao_id_;
    GLuint positions_vbo_id_;
    GLuint texture_cooordinates_vbo_id_;
    GLuint indices_vbo_id_;
};

}  // namespace image_processor::model::texture_processors

#endif  // IMAGEPROCESSOR_GL_TEXTURE_PROCESSOR_H
