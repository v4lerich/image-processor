#include "gl_texture_kernel_processor.h"

namespace image_processor::model::texture_processors {

GlTextureKernelProcessor::GlTextureKernelProcessor(const shader_programs::GlKernelBasedShaderProgram& program,
                                                   const Kernel& kernel)
    : program_{program},
      kernel_{kernel},
      kernel_texture_{std::move(CreateKernelGlTexture(kernel))} {}

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

auto GlTextureKernelProcessor::CreateKernelGlTexture(const Kernel& kernel) -> GlTexture {
    GLuint kernel_texture;
    glGenTextures(1, &kernel_texture);
    glBindTexture(GL_TEXTURE_2D, kernel_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    std::array<float, 4> border_color{0.0f, 0.0f, 0.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color.data());

    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, kernel.GetWidth(), kernel.GetHeight(), 0, GL_RED,
                 GL_FLOAT, kernel.GetData());

    glBindTexture(GL_TEXTURE_2D, 0);

    return {kernel_texture, static_cast<GLsizei>(kernel.GetWidth()),
            static_cast<GLsizei>(kernel.GetHeight())};
}

}  // namespace image_processor::model::texture_processors
