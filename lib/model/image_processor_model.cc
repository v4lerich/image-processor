#include "image_processor_model.h"

namespace image_processor::model {

ImageProcessorModel::ImageProcessorModel() = default;

auto ImageProcessorModel::GetInitialTexture() const -> const std::optional<GlTexture>& {
    return initial_texture_;
}

void ImageProcessorModel::SetInitialTexture(GlTexture texture) {
    initial_texture_ = std::make_optional(std::move(texture));
}

}  // namespace image_processor::model
