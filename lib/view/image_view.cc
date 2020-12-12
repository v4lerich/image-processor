#include "image_view.h"

#include <imgui.h>
#include <imgui_internal.h>

#include <utility>

namespace image_processor::view {

ImageView::ImageView(std::string window_name, Model& model)
    : model_(model), window_name_(std::move(window_name)) {}

void ImageView::Render() {
    if (ImGui::Begin(window_name_.c_str())) {
        if (const auto &texture = model_.GetInitialTexture(); texture) {
            const auto imgui_image = texture->id;
            const ImVec2 image_size{static_cast<float>(texture->width),
                                    static_cast<float>(texture->height)};
            glBindTexture(GL_TEXTURE_2D, imgui_image);
            ImGui::Image((ImTextureID)imgui_image, image_size);
        }
        ImGui::End();
    }
}

}  // namespace image_processor::view
