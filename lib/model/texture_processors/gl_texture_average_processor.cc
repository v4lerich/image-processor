#include "gl_texture_average_processor.h"

namespace image_processor::model::texture_processors {

GlTextureAverageProcessor::GlTextureAverageProcessor(
    const shader_programs::GlAverageShaderProgram& program, int width_half_size,
    int height_half_size)
    : program_{program}, width_half_size_{width_half_size}, height_half_size_{height_half_size} {}

void GlTextureAverageProcessor::PrepareProcessing(const GlTexture& texture) {
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

    glUniform2i(program_.GetKernelHalfSizeUniform(), width_half_size_, height_half_size_);
}

}  // namespace image_processor::model::texture_processors
