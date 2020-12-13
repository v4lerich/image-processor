#include "gl_texture.h"

#include <memory>

namespace image_processor::model {
GlTexture::GlTexture(GLuint id, GLsizei width, GLsizei height)
    : id(id), width(width), height(height) {}

GlTexture::GlTexture(GlTexture&& other) noexcept { *this = std::move(other); }

GlTexture::~GlTexture() {
    if (id != 0) {
        glDeleteTextures(1, &id);
    }
}
GlTexture& GlTexture::operator=(GlTexture&& other) {
    *this = other;
    other.id = 0;
    return *this;
}
}  // namespace image_processor::model
