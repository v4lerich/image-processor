#include "texture_processor_view.h"

#include <imgui.h>
#include <imgui_internal.h>
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
    const auto start_position = ImGui::GetCursorScreenPos();
    ImGui::SetCursorScreenPos(start_position + kPadding);

    ImGui::BeginGroup();

    ImGui::BeginGroup();
    ImGui::Text("%s", GetTitle().c_str());
    RenderParameters();
    ImGui::EndGroup();

    ImGui::SameLine();
    ImGui::BeginGroup();
    if (ImGui::Button(" x ##close")) SetWantClose();
    want_move_up_ = ImGui::ArrowButton("##arrow_up", ImGuiDir_Up);
    want_move_down_ = ImGui::ArrowButton("##arrow_down", ImGuiDir_Down);
    ImGui::EndGroup();

    ImGui::EndGroup();

    const auto end_position = ImGui::GetItemRectMax() + kPadding;
    ImGui::Dummy(kPadding);
    ImGui::GetWindowDrawList()->AddRect(start_position, end_position,
                                        ImColor(ImGui::GetStyle().Colors[ImGuiCol_Border]));
}

auto TextureProcessorView::GetFactory() -> TextureProcessorView::Factory& { return factory_; }

void TextureProcessorView::SetChanged() {
    changed_ = true;
}

}  // namespace image_processor::view::texture_processors
