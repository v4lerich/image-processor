#ifndef IMAGEPROCESSOR_GL_TEXTURE_AVERAGE_PROCESSOR_H
#define IMAGEPROCESSOR_GL_TEXTURE_AVERAGE_PROCESSOR_H

#include <gl_texture.h>
#include <kernel.h>

#include "gl_texture_processor.h"
#include "shader_programs/gl_average_shader_program.h"

namespace image_processor::model::texture_processors {

class GlTextureAverageProcessor : public GlTextureProcessor {
  public:
    GlTextureAverageProcessor(const shader_programs::GlAverageShaderProgram& program,
                              int width_half_size, int height_half_size);

  protected:
    void PrepareProcessing(const GlTexture& texture) override;

  private:
    const shader_programs::GlAverageShaderProgram& program_;
    int width_half_size_;
    int height_half_size_;
};

}  // namespace image_processor::model::texture_processors

#endif  // IMAGEPROCESSOR_GL_TEXTURE_AVERAGE_PROCESSOR_H
