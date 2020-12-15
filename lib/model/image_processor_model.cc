#include "image_processor_model.h"

#include <filesystem>
#include <string>

#include "kernel.h"
#include "texture_processors/gl_texture_kernel_processor.h"
#include "texture_processors/gl_texture_average_processor.h"

namespace image_processor::model {

ImageProcessorModel::ImageProcessorModel() = default;

auto ImageProcessorModel::GetInitialTexture() const -> const std::optional<GlTexture>& {
    return initial_texture_;
}

void ImageProcessorModel::SetInitialTexture(GlTexture texture) {
//    std::vector<std::vector<float>> coefficients = {
//        {1.0f, +1.0f, 1.0f},  //
//        {1.0f, -8.0f, 1.0f},  //
//        {1.0f, +1.0f, 1.0f},  //
//    };
//    Kernel kernel{coefficients};
//    texture_processors::GlTextureKernelProcessor processor{program_, kernel};

    texture_processors::GlTextureAverageProcessor processor{average_program_, 10, 2};

    auto processed_texture = processor.Process(texture);
    initial_texture_ = std::make_optional(std::move(processed_texture));
    //    initial_texture_ = std::make_optional(std::move(texture));
}

}  // namespace image_processor::model
