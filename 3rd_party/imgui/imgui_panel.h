// Thanks @thedmd
// From https://github.com/ocornut/imgui/issues/1496#issuecomment-655048353

#ifndef IMAGEPROCESSOR_IMGUI_PANEL_H
#define IMAGEPROCESSOR_IMGUI_PANEL_H

#include "imgui.h"

namespace ImGui {

void BeginGroupPanel(const char* name, const ImVec2& size = ImVec2(0.0f, 0.0f));
void EndGroupPanel();

}  // namespace ImGui

#endif  // IMAGEPROCESSOR_IMGUI_PANEL_H
