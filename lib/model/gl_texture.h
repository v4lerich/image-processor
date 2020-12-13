#ifndef IMAGEPROCESSOR_GL_TEXTURE_H
#define IMAGEPROCESSOR_GL_TEXTURE_H

#include <glad/gl.h>

namespace image_processor::model {

struct GlTexture {
    GlTexture(GLuint id, GLsizei width, GLsizei height);
    GlTexture(GlTexture&& other) noexcept;
    GlTexture& operator=(GlTexture&& other);
    ~GlTexture();

    GLuint id;
    GLsizei width;
    GLsizei height;

  private:
    GlTexture(const GlTexture& other) = default;
    GlTexture& operator=(const GlTexture& other) = default;
};

}  // namespace image_processor::model

#endif  // IMAGEPROCESSOR_GL_TEXTURE_H
