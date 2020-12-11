#ifndef IMAGEPROCESSOR_APPLICATION_H
#define IMAGEPROCESSOR_APPLICATION_H

#include <SDL.h>
#include <imgui.h>

namespace image_processor {

class Application {
  public:
    using ReturnCode = int;

    Application(int argc, char** argv);
    auto Init() -> ReturnCode;
    auto Run() -> ReturnCode;

  private:
    static auto InitSdl() -> ReturnCode;
    auto InitImGui() -> ReturnCode;
    auto CreateMainWindow() -> ReturnCode;
    auto Finalize() -> ReturnCode;

    void ProcessSdlEvent(const SDL_Event& event);
    void RenderViews();

    SDL_Window* main_window_{};
    SDL_GLContext gl_context_{};
    ImGuiIO *imgui_io_{};
    bool done_{};
};

}  // namespace image_processor

#endif  // IMAGEPROCESSOR_APPLICATION_H
