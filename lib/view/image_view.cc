#include "image_view.h"

#include <imgui.h>
#include <imgui_internal.h>

#include <utility>

namespace image_processor::view {

ImageView::ImageView(std::string window_name, Model& model)
    : model_(model), window_name_(std::move(window_name)) {}

void ImageView::RenderIndexed() {
    ImGuiWindowFlags window_flags{ImGuiWindowFlags_HorizontalScrollbar |
                                  ImGuiWindowFlags_NoScrollWithMouse};
    if (ImGui::Begin(window_name_.c_str(), nullptr, window_flags)) {
        if (const auto& texture = model_.GetResultTexture(); texture) {
            const auto imgui_image = texture->GetId();
            const ImVec2 image_size{static_cast<float>(texture->width),
                                    static_cast<float>(texture->height)};

            ImGui::SetCursorPos((ImGui::GetWindowSize() - image_size) / 2);
            ImGui::Image((ImTextureID)imgui_image, image_size * zoom_);
        }

        if (ImGui::IsWindowHovered()) {
            auto delta = ImGui::GetIO().MouseWheel;
            auto delta_h = ImGui::GetIO().MouseWheelH;

            auto zoom_delta = 1.0f + delta * 0.25f;
            zoom_ *= std::max(zoom_delta, 0.25f);
        }

        if (ImGui::IsWindowHovered() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
            auto delta = ImGui::GetIO().MouseDelta;
            ImGui::SetScrollX(ImGui::GetScrollX() - delta.x);
            ImGui::SetScrollY(ImGui::GetScrollY() - delta.y);
        }

        ImGui::End();
    }
}

}  // namespace image_processor::view
