#include "gl_texture.h"

#include <memory>

namespace image_processor::model {
GlTexture::GlTexture(GLuint id, GLsizei width, GLsizei height)
    : id_(new GLuint(id), DeleteGlTexture), width{width}, height{height} {}

void GlTexture::DeleteGlTexture(GLuint* texture_id) {
    if (*texture_id != 0) glDeleteTextures(1, texture_id);
}

auto GlTexture::GetId() const -> GLuint { return *id_; }

}  // namespace image_processor::model
