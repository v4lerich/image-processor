#ifndef IMAGEPROCESSOR_IMAGE_PROCESSOR_MODEL_H
#define IMAGEPROCESSOR_IMAGE_PROCESSOR_MODEL_H

#include <glad/gl.h>

#include <optional>

namespace image_processor::model {

struct GlTexture {
    GlTexture(GLuint id, GLsizei width, GLsizei height);
    GlTexture(GlTexture&& other) noexcept ;
    GlTexture& operator=(GlTexture&& other);
    ~GlTexture();

    GLuint id;
    GLsizei width;
    GLsizei height;

  private:
    GlTexture(const GlTexture& other) = default;
    GlTexture& operator=(const GlTexture& other) = default;
};

class ImageProcessorModel {
  public:
    ImageProcessorModel();

    [[nodiscard]] auto GetInitialTexture() const -> const std::optional<GlTexture>&;
    void SetInitialTexture(GlTexture texture);

  private:
    std::optional<GlTexture> initial_texture_{};
};

}  // namespace image_processor::model

#endif  // IMAGEPROCESSOR_IMAGE_PROCESSOR_MODEL_H
