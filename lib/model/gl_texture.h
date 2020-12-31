#ifndef IMAGEPROCESSOR_GL_TEXTURE_H
#define IMAGEPROCESSOR_GL_TEXTURE_H

#include <glad/gl.h>

#include <memory>

namespace image_processor::model {

struct GlTexture {
    GlTexture(GLuint id, GLsizei width, GLsizei height);

    auto GetId() const -> GLuint;

    GLsizei width;
    GLsizei height;

  private:
    static void DeleteGlTexture(GLuint* texture_id);

    std::shared_ptr<GLuint> id_;
};

}  // namespace image_processor::model

#endif  // IMAGEPROCESSOR_GL_TEXTURE_H
