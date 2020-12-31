#include "kernel_texture_processor_view.h"

#include <texture_processors/gl_texture_kernel_processor.h>

namespace image_processor::view::texture_processors {

KernelTextureProcessorView::KernelTextureProcessorView(Factory& factory)
    : TextureProcessorView{factory} {}

void KernelTextureProcessorView::RenderParameters() {
    bool changed = false;
//    changed |= ImGui::InputInt("Half width", &half_width_, 1, 0);
//    half_width_ = std::clamp(half_width_, 0, 3);
//
//    changed |= ImGui::InputInt("Half height", &half_height_, 1, 0);
//    half_height_ = std::clamp(half_height_, 0, 3);
//
    if (changed) SetChanged();
}

auto KernelTextureProcessorView::GetTitle() -> std::string { return "Kernel filter"; }

auto KernelTextureProcessorView::CreateTextureProcessor() -> std::unique_ptr<TextureProcessor> {
    std::vector<std::vector<float>> coefficients = {
        {1.0f, +1.0f, 1.0f},  //
        {1.0f, -8.0f, 1.0f},  //
        {1.0f, +1.0f, 1.0f},  //
    };
    model::Kernel kernel{coefficients};
    return GetFactory().CreateKernelTextureProcessor(kernel);
}

}  // namespace image_processor::view::texture_processors
