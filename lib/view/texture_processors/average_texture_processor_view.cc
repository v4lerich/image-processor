#include "average_texture_processor_view.h"

#include <texture_processors/gl_texture_average_processor.h>

namespace image_processor::view::texture_processors {

AverageTextureProcessorView::AverageTextureProcessorView(Factory& factory)
    : TextureProcessorView{factory} {}

void AverageTextureProcessorView::RenderParameters() {
    bool changed = false;
    changed |= ImGui::InputInt("Half width", &half_width_, 1, 0);
    half_width_ = std::clamp(half_width_, 0, 10);

    changed |= ImGui::InputInt("Half height", &half_height_, 1, 0);
    half_height_= std::clamp(half_height_, 0, 10);

    if (changed) SetChanged();
}

auto AverageTextureProcessorView::GetTitle() -> std::string { return "Average filter"; }

auto AverageTextureProcessorView::CreateTextureProcessor() -> std::unique_ptr<TextureProcessor> {
    return GetFactory().CreateAverageTextureProcessor(half_width_, half_height_);
}

}  // namespace image_processor::view::texture_processors
