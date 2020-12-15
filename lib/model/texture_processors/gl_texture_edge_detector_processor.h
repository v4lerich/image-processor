#ifndef IMAGEPROCESSOR_GL_TEXTURE_EDGE_DETECTOR_PROCESSOR_H
#define IMAGEPROCESSOR_GL_TEXTURE_EDGE_DETECTOR_PROCESSOR_H

#include <gl_texture.h>
#include <kernel.h>

#include "gl_texture_processor.h"
#include "shader_programs/gl_edge_detector_shader_program.h"

namespace image_processor::model::texture_processors {

class GlTextureEdgeDetectorProcessor : public GlTextureProcessor {
  public:
    GlTextureEdgeDetectorProcessor(const shader_programs::GlEdgeDetectorShaderProgram& program,
                                   const Kernel& x_kernel, const Kernel& y_kernel);

  protected:
    void PrepareProcessing(const GlTexture& texture) override;

  private:
    const GlTexture x_kernel_texture_;
    const GlTexture y_kernel_texture_;
    const shader_programs::GlEdgeDetectorShaderProgram& program_;
};

}  // namespace image_processor::model::texture_processors

#endif  // IMAGEPROCESSOR_GL_TEXTURE_EDGE_DETECTOR_PROCESSOR_H
