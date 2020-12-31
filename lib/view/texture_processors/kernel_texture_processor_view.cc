#include "kernel_texture_processor_view.h"

#include <texture_processors/gl_texture_kernel_processor.h>

namespace image_processor::view::texture_processors {

KernelTextureProcessorView::KernelTextureProcessorView(Factory& factory)
    : TextureProcessorView{factory} {
    UpdateCoefficientsSize();
}

void KernelTextureProcessorView::RenderParameters() {
    bool changed = false;
    changed |= ImGui::InputInt("Half width", &half_width_, 1, 0);
    half_width_ = std::clamp(half_width_, 0, 3);

    changed |= ImGui::InputInt("Half height", &half_height_, 1, 0);
    half_height_ = std::clamp(half_height_, 0, 3);

    ImGui::NewLine();

    if (changed) UpdateCoefficientsSize();

    if (ImGui::BeginChild("Coefficients", {0, 200}, true, ImGuiWindowFlags_HorizontalScrollbar)) {
        ImGuiID row_id = 0;
        for (auto& row : coefficients_) {
            ImGui::PushID(row_id++);
            ImGuiID coefficient_id = 0;
            for (auto& coefficient : row) {
                ImGui::PushID(coefficient_id++);
                ImGui::PushItemWidth(40);
                changed |= ImGui::DragFloat("", &coefficient, 0.1f, -10.0f, +10.0f, "%.2f",
                                            ImGuiSliderFlags_AlwaysClamp);
                ImGui::PopItemWidth();
                ImGui::PopID();
                ImGui::SameLine();
            }
            ImGui::PopID();
            ImGui::Dummy({0, 0});
        }
        ImGui::EndChild();
    }

    if (changed) SetChanged();
}

void KernelTextureProcessorView::UpdateCoefficientsSize() {
    coefficients_.resize(2 * half_height_ + 1);
    for (auto& row : coefficients_) {
        row.resize(2 * half_width_ + 1);
    }
}

auto KernelTextureProcessorView::GetTitle() -> std::string { return "Kernel filter"; }

auto KernelTextureProcessorView::CreateTextureProcessor() -> std::unique_ptr<TextureProcessor> {
    return GetFactory().CreateKernelTextureProcessor({coefficients_});
}

}  // namespace image_processor::view::texture_processors
