#include "view.h"

namespace image_processor::view {

ImGuiID View::id_counter_ = 0;

View::View() : id_{NextId()} {}

void View::Render() {
    ImGui::PushID(id_);
    this->RenderIndexed();
    ImGui::PopID();
}

auto View::WantClose() -> bool { return want_close_; }

void View::SetWantClose() { want_close_ = true; }

auto View::NextId() -> ImGuiID { return id_counter_++; }

}  // namespace image_processor::view
