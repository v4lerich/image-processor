#include "image_processor_model.h"

namespace image_processor::model {

GlTexture::GlTexture(GLuint id, GLsizei width, GLsizei height)
    : id(id), width(width), height(height) {}

GlTexture::GlTexture(GlTexture&& other) noexcept {
    *this = std::move(other);
}

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

ImageProcessorModel::ImageProcessorModel() = default;

auto ImageProcessorModel::GetInitialTexture() const -> const std::optional<GlTexture>& {
    return initial_texture_;
}

void ImageProcessorModel::SetInitialTexture(GlTexture texture) {
    initial_texture_ = std::make_optional(std::move(texture));
}

}  // namespace image_processor::model
