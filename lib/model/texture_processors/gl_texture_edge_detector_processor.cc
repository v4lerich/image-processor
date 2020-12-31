#include "gl_texture_edge_detector_processor.h"

namespace image_processor::model::texture_processors {

GlTextureEdgeDetectorProcessor::GlTextureEdgeDetectorProcessor(
    const shader_programs::GlEdgeDetectorShaderProgram& program, const Kernel& x_kernel,
    const Kernel& y_kernel)
    : program_{program},
      x_kernel_texture_{std::move(CreateKernelGlTexture(x_kernel))},
      y_kernel_texture_{std::move(CreateKernelGlTexture(y_kernel))} {}

void GlTextureEdgeDetectorProcessor::PrepareProcessing(const GlTexture& texture) {
    glUseProgram(program_.GetID());

    glBindBuffer(GL_ARRAY_BUFFER, GetPositionsVbo());
    glVertexAttribPointer(program_.GetPositionsAttribute(), 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(program_.GetPositionsAttribute());

    glBindBuffer(GL_ARRAY_BUFFER, GetTextureCoordinatesVbo());
    glVertexAttribPointer(program_.GetTextureCoordinateAttribute(), 2, GL_FLOAT, GL_FALSE, 0,
                          nullptr);
    glEnableVertexAttribArray(program_.GetTextureCoordinateAttribute());

    glUniform1i(program_.GetImageUniform(), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.GetId());
    glBindSampler(0, texture.GetId());

    glUniform1i(program_.GetXKernelUniform(), 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, x_kernel_texture_.GetId());
    glBindSampler(1, x_kernel_texture_.GetId());

    glUniform1i(program_.GetYKernelUniform(), 2);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, y_kernel_texture_.GetId());
    glBindSampler(2, y_kernel_texture_.GetId());
}

}  // namespace image_processor::model::texture_processors
