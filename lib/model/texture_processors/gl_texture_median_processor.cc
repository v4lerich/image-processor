#include "gl_texture_median_processor.h"

namespace image_processor::model::texture_processors {

GlTextureMedianProcessor::GlTextureMedianProcessor(
    const shader_programs::GlMedianShaderProgram& program)
    : program_{program} {}

void GlTextureMedianProcessor::PrepareProcessing(const GlTexture& texture) {
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
}

}  // namespace image_processor::model::texture_processors
