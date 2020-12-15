#include "gl_texture_kernel_processor.h"

namespace image_processor::model::texture_processors {

GlTextureKernelProcessor::GlTextureKernelProcessor(
    const shader_programs::GlKernelBasedShaderProgram& program, const Kernel& kernel)
    : program_{program}, kernel_texture_{std::move(CreateKernelGlTexture(kernel))} {}

void GlTextureKernelProcessor::PrepareProcessing(const GlTexture& texture) {
    glUseProgram(program_.GetID());

    glBindBuffer(GL_ARRAY_BUFFER, GetPositionsVbo());
    glVertexAttribPointer(program_.GetPositionsAttribute(), 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(program_.GetPositionsAttribute());

    glBindBuffer(GL_ARRAY_BUFFER, GetPositionsVbo());
    glVertexAttribPointer(program_.GetTextureCoordinateAttribute(), 2, GL_FLOAT, GL_FALSE, 0,
                          nullptr);
    glEnableVertexAttribArray(program_.GetTextureCoordinateAttribute());

    glUniform1i(program_.GetImageUniform(), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glBindSampler(0, texture.id);

    glUniform1i(program_.GetKernelUniform(), 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, kernel_texture_.id);
    glBindSampler(1, kernel_texture_.id);
}

}  // namespace image_processor::model::texture_processors
