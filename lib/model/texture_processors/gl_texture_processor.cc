#include "gl_texture_processor.h"

#include <array>

namespace image_processor::model::texture_processors {

static const std::vector<unsigned int> kImageVertexIndices{
    0, 1, 3,  //
    0, 3, 2,  //
};

static const std::vector<float> kImageVertices{
    0.0f, 0.0f,  //
    0.0f, 1.0f,  //
    1.0f, 0.0f,  //
    1.0f, 1.0f,  //
};

static const std::vector<float> kImageTextureCoordinates{
    0.0f, 0.0f,  //
    0.0f, 1.0f,  //
    1.0f, 0.0f,  //
    1.0f, 1.0f,  //
};

GlTextureProcessor::GlTextureProcessor() {}

auto GlTextureProcessor::Process(const GlTexture& texture) -> GlTexture {
    GlTexture processing_texture = CreateProcessingTexture(texture);
    GLuint framebuffer = CreateProcessingFramebuffer(processing_texture);

    CreateTextureBoxVao(texture);
    CreateTextureBoxIndexVbo();

    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glViewport(0, 0, texture.width, texture.height);

    glBindVertexArray(vao_id_);

    PrepareProcessing(texture);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo_id_);
    glDrawElements(GL_TRIANGLES, kImageVertexIndices.size(), GL_UNSIGNED_INT, nullptr);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glDeleteFramebuffers(1, &framebuffer);

    return processing_texture;
}

void GlTextureProcessor::CreateTextureBoxVao(const GlTexture& texture) {
    float width = texture.width;
    float height = texture.width;

    glGenVertexArrays(1, &vao_id_);
    glBindVertexArray(vao_id_);

    std::array<GLuint, 2> vbos{};
    glGenBuffers(vbos.size(), vbos.data());
    positions_vbo_id_ = vbos[0];
    texture_cooordinates_vbo_id_ = vbos[1];

    glBindBuffer(GL_ARRAY_BUFFER, positions_vbo_id_);
    glBufferData(GL_ARRAY_BUFFER,
                 kImageVertices.size() * sizeof(decltype(kImageVertices)::value_type),
                 kImageVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, texture_cooordinates_vbo_id_);
    glBufferData(
        GL_ARRAY_BUFFER,
        kImageTextureCoordinates.size() * sizeof(decltype(kImageTextureCoordinates)::value_type),
        kImageTextureCoordinates.data(), GL_STATIC_DRAW);

    CreateTextureBoxIndexVbo();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GlTextureProcessor::CreateTextureBoxIndexVbo() {
    glGenBuffers(1, &indices_vbo_id_);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo_id_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 kImageVertexIndices.size() * sizeof(decltype(kImageVertexIndices)::value_type),
                 kImageVertexIndices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

auto GlTextureProcessor::CreateProcessingFramebuffer(const GlTexture& rendered_texture) -> GLuint {
    GLuint framebuffer;
    auto e = glGetError();
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, rendered_texture.id,
                           0);
    return framebuffer;
}

auto GlTextureProcessor::CreateProcessingTexture(const GlTexture& texture) -> GlTexture {
    GLuint rendered_texture;
    glGenTextures(1, &rendered_texture);
    glBindTexture(GL_TEXTURE_2D, rendered_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, nullptr);

    glBindTexture(GL_TEXTURE_2D, 0);

    return {rendered_texture, texture.width, texture.height};
}

auto GlTextureProcessor::CreateKernelGlTexture(const Kernel& kernel) -> GlTexture {
    GLuint kernel_texture;
    glGenTextures(1, &kernel_texture);
    glBindTexture(GL_TEXTURE_2D, kernel_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
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
