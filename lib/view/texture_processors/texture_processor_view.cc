#include "texture_processor_view.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_panel.h>
#include <texture_processors/gl_texture_median_processor.h>

namespace image_processor::view::texture_processors {

static const std::string kTextureProcessorChildWindowName = "image_processor";
static const ImVec2 kPadding = {4.0f, 4.0f};

TextureProcessorView::TextureProcessorView(TextureProcessorView::Factory& factory)
    : factory_{factory} {}

auto TextureProcessorView::Changed() -> bool { return changed_; }

auto TextureProcessorView::WantMoveUp() -> bool { return want_move_up_; }

auto TextureProcessorView::WantMoveDown() -> bool { return want_move_down_; }

void TextureProcessorView::RenderIndexed() {
    changed_ = false;
    ImGui::BeginGroupPanel("Kek", {0, 0});

    ImGui::BeginGroup();
    ImGui::Text("%s", GetTitle().c_str());
    RenderParameters();
    ImGui::EndGroup();

    ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::GetFrameHeight() - 10);
    ImGui::BeginGroup();
    if (ImGui::Button(" x ##close")) SetWantClose();
    want_move_up_ = ImGui::ArrowButton("##arrow_up", ImGuiDir_Up);
    want_move_down_ = ImGui::ArrowButton("##arrow_down", ImGuiDir_Down);
    ImGui::EndGroup();

    ImGui::EndGroupPanel();
}

auto TextureProcessorView::GetFactory() -> TextureProcessorView::Factory& { return factory_; }

void TextureProcessorView::SetChanged() { changed_ = true; }

}  // namespace image_processor::view::texture_processors
