#ifndef IMAGEPROCESSOR_VIEW_H
#define IMAGEPROCESSOR_VIEW_H

#include <imgui.h>

namespace image_processor::view {

class View {
  public:
    View();
    virtual ~View() = default;

    void Render();
    virtual auto WantClose() -> bool;

  protected:
    static auto NextId() -> ImGuiID;

    void SetWantClose();
    virtual void RenderIndexed() = 0;

  private:
    static ImGuiID id_counter_;
    ImGuiID id_;
    bool want_close_{false};
};

}  // namespace image_processor::view

#endif  // IMAGEPROCESSOR_VIEW_H
