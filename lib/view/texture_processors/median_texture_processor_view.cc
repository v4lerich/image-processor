#include "median_texture_processor_view.h"

#include <texture_processors/gl_texture_median_processor.h>

namespace image_processor::view::texture_processors {

MedianTextureProcessorView::MedianTextureProcessorView(Factory& factory)
    : TextureProcessorView{factory} {}

void MedianTextureProcessorView::RenderParameters() {
    bool changed = false;
    changed |= ImGui::InputInt("Half width", &half_width_, 1, 0);
    half_width_ = std::clamp(half_width_, 0, 2);

    changed |= ImGui::InputInt("Half height", &half_height_, 1, 0);
    half_height_= std::clamp(half_height_, 0, 2);

    if (changed) SetChanged();
}

auto MedianTextureProcessorView::GetTitle() -> std::string { return "Median filter"; }

auto MedianTextureProcessorView::CreateTextureProcessor() -> std::unique_ptr<TextureProcessor> {
    return GetFactory().CreateMedianTextureProcessor(half_width_, half_height_);
}

}  // namespace image_processor::view::texture_processors
