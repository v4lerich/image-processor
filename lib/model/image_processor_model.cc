#include "image_processor_model.h"

#include <filesystem>
#include <string>

#include "kernel.h"
#include "texture_processors/gl_texture_average_processor.h"
#include "texture_processors/gl_texture_edge_detector_processor.h"
#include "texture_processors/gl_texture_kernel_processor.h"
#include "texture_processors/gl_texture_median_processor.h"

namespace image_processor::model {

ImageProcessorModel::ImageProcessorModel() = default;

auto ImageProcessorModel::GetInitialTexture() const -> const std::optional<GlTexture>& {
    return initial_texture_;
}

auto ImageProcessorModel::GetResultTexture() const -> const std::optional<GlTexture>& {
    return result_texture_;
}

void ImageProcessorModel::SetInitialTexture(GlTexture texture) {
    initial_texture_ = std::make_optional(std::move(texture));
    ProcessTexture();
}

auto ImageProcessorModel::GetTextureProcessorFactory()
    -> texture_processors::GlTextureProcessorFactory& {
    return texture_processor_factory_;
}

void ImageProcessorModel::ProcessTexture() {
    if (initial_texture_) {
        result_texture_ = initial_texture_;
        for (const auto& texture_processor : texture_processors_) {
            result_texture_ = texture_processor->Process(*result_texture_);
        }
    } else {
        result_texture_ = std::nullopt;
    }
}

}  // namespace image_processor::model
