#include "image_processor_model.h"

#include <filesystem>
#include <string>

#include "gl_texture_kernel_processor.h"
#include "kernel.h"

namespace image_processor::model {

static const std::filesystem::path kVertexShaderPath =
    std::filesystem::path{std::string{"./res/shaders/kernel_processor.vert"}};
static const std::filesystem::path kFragmentShaderPath =
    std::filesystem::path{std::string{"./res/shaders/kernel_processor.frag"}};

ImageProcessorModel::ImageProcessorModel() : program_{kVertexShaderPath, kFragmentShaderPath} {}

auto ImageProcessorModel::GetInitialTexture() const -> const std::optional<GlTexture>& {
    return initial_texture_;
}

void ImageProcessorModel::SetInitialTexture(GlTexture texture) {
    std::vector<std::vector<float>> coefficients = {
        {1.0f, 2.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {-1.0f, -2.0f, -1.0f}};
    Kernel kernel{coefficients};
    GlTextureKernelProcessor processor{program_, kernel};

    auto processed_texture = processor.Process(texture);
    initial_texture_ = std::make_optional(std::move(processed_texture));
}

}  // namespace image_processor::model
