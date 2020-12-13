#ifndef IMAGEPROCESSOR_IMAGE_PROCESSOR_MODEL_H
#define IMAGEPROCESSOR_IMAGE_PROCESSOR_MODEL_H

#include <glad/gl.h>

#include <optional>

#include "gl_texture.h"

namespace image_processor::model {

class ImageProcessorModel final {
  public:
    ImageProcessorModel();

    [[nodiscard]] auto GetInitialTexture() const -> const std::optional<GlTexture>&;
    void SetInitialTexture(GlTexture texture);

  private:
    std::optional<GlTexture> initial_texture_{};
};

}  // namespace image_processor::model

#endif  // IMAGEPROCESSOR_IMAGE_PROCESSOR_MODEL_H
