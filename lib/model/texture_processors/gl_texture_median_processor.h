#ifndef IMAGEPROCESSOR_GL_TEXTURE_MEDIAN_PROCESSOR_H
#define IMAGEPROCESSOR_GL_TEXTURE_MEDIAN_PROCESSOR_H

#include <gl_texture.h>
#include <kernel.h>

#include "gl_texture_processor.h"
#include "shader_programs/gl_median_shader_program.h"

namespace image_processor::model::texture_processors {

class GlTextureMedianProcessor : public GlTextureProcessor {
  public:
    explicit GlTextureMedianProcessor(const shader_programs::GlMedianShaderProgram& program);

  protected:
    void PrepareProcessing(const GlTexture& texture) override;

  private:
    const shader_programs::GlMedianShaderProgram& program_;
};

}  // namespace image_processor::model::texture_processors

#endif  // IMAGEPROCESSOR_GL_TEXTURE_MEDIAN_PROCESSOR_H
