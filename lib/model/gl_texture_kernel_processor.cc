#include "gl_texture_kernel_processor.h"

#include <array>

namespace image_processor::model {

std::vector<unsigned int> kImageVertexIndices{
    0, 1, 3,  //
    0, 3, 2,  //
};

GlImageKernelProcessor::GlImageKernelProcessor(const GlKernelProcessorShaderProgram& program,
                                               const Kernel& kernel)
    : program_{program},
      kernel_{kernel},
      kernel_texture_{std::move(CreateKernelGlTexture(kernel))} {}

static const int kPositionAttributeId = 0;
static const int kTextureCoordinateAttributeId = 1;

auto GlImageKernelProcessor::Process(const GlTexture& texture) -> GlTexture {
    GlTexture processing_texture = CreateProcessingTexture(texture);
    GLuint framebuffer = CreateProcessingFramebuffer(processing_texture);

    CreateTextureBoxVao(texture);
    CreateTextureBoxIndexVbo();

    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glViewport(0, 0, texture.width, texture.height);

    glBindVertexArray(vao_id_);

    glUseProgram(program_.GetID());

    glEnableVertexAttribArray(kPositionAttributeId);
    glEnableVertexAttribArray(kTextureCoordinateAttributeId);

    glUniform1i(program_.GetImageUniform(), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glBindSampler(0, texture.id);

    glUniform1i(program_.GetImageUniform(), 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, kernel_texture_.id);
    glBindSampler(1, texture.id);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo_id_);
    glDrawElements(GL_TRIANGLES, kImageVertexIndices.size(), GL_UNSIGNED_INT, nullptr);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glDeleteFramebuffers(1, &framebuffer);

    return processing_texture;
}

void GlImageKernelProcessor::CreateTextureBoxVao(const GlTexture& texture) {
    float width = texture.width;
    float height = texture.width;

    std::vector<float> image_vertices = {
        0.0f,   0.0f,   //
        0.0f,   width,  //
        height, 0.0f,   //
        height, width,  //
    };

    std::vector<float> image_texture_coordinates = {
        0.0f, 0.0f,  //
        0.0f, 1.0f,  //
        1.0f, 0.0f,  //
        1.0f, 1.0f,  //
    };

    glGenVertexArrays(1, &vao_id_);
    glBindVertexArray(vao_id_);

    std::array<GLuint, 2> vbos{};
    glGenBuffers(vbos.size(), vbos.data());
    positions_vbo_id_ = vbos[0];
    texture_cooordinates_vbo_id_ = vbos[1];

    glBindBuffer(GL_ARRAY_BUFFER, positions_vbo_id_);
    glBufferData(GL_ARRAY_BUFFER,
                 image_vertices.size() * sizeof(decltype(image_vertices)::value_type),
                 image_vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(program_.GetPositionsAttribute(), 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, texture_cooordinates_vbo_id_);
    glBufferData(
        GL_ARRAY_BUFFER,
        image_texture_coordinates.size() * sizeof(decltype(image_texture_coordinates)::value_type),
        image_texture_coordinates.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(program_.GetTextureCoordinateAttribute(), 2, GL_FLOAT, GL_FALSE, 0,
                          nullptr);

    CreateTextureBoxIndexVbo();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GlImageKernelProcessor::CreateTextureBoxIndexVbo() {
    glGenBuffers(1, &indices_vbo_id_);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo_id_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 kImageVertexIndices.size() * sizeof(decltype(kImageVertexIndices)::value_type),
                 kImageVertexIndices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

auto GlImageKernelProcessor::CreateProcessingFramebuffer(const GlTexture& rendered_texture)
    -> GLuint {
    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    const auto color_buffer = GL_COLOR_ATTACHMENT0;
    glFramebufferTexture2D(GL_FRAMEBUFFER, color_buffer, GL_TEXTURE_2D, rendered_texture.id, 0);
    glDrawBuffer(color_buffer);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        exit(-2);
    }
    return framebuffer;
}

auto GlImageKernelProcessor::CreateProcessingTexture(const GlTexture& texture) -> GlTexture {
    GLuint rendered_texture;
    glGenTextures(1, &rendered_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    return {rendered_texture, texture.width, texture.height};
}

auto GlImageKernelProcessor::CreateKernelGlTexture(const Kernel& kernel) -> GlTexture {
    GLuint kernel_texture;
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &kernel_texture);
    glBindTexture(GL_TEXTURE_2D, kernel_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    std::array<float, 4> border_color{0.0f, 0.0f, 0.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color.data());

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, kernel.GetWidth(), kernel.GetHeight(), 0,
                 GL_DEPTH_COMPONENT, GL_FLOAT, kernel.GetData());

    return {kernel_texture, static_cast<GLsizei>(kernel.GetWidth()),
            static_cast<GLsizei>(kernel.GetHeight())};
}

}  // namespace image_processor::model
