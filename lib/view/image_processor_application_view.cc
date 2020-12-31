#include "image_processor_application_view.h"

#include <imgui.h>
#include <imgui_internal.h>

#include <string>

namespace image_processor::view {

const std::string kDockspaceName = "main_dockspace";
const std::string kImageViewWindowName = "image_view";
const std::string kTextureProcessorsListView = "texture_processors";

ImageProcessorApplicationView::ImageProcessorApplicationView(Model& model)
    : image_view_{kImageViewWindowName, model},
      texture_processors_list_view_{model, kTextureProcessorsListView},
      file_dialog_view_{model} {}

void ImageProcessorApplicationView::RenderIndexed() {
    if (BeginDockingWindow()) {
        RenderMenuBar();

        ImGuiWindowClass window_class;
        window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar;

        ImGui::SetNextWindowClass(&window_class);
        image_view_.Render();

        ImGui::SetNextWindowClass(&window_class);
        texture_processors_list_view_.Render();

        EndDockingWindow();
    }

    file_dialog_view_.Render();
}

auto ImageProcessorApplicationView::BeginDockingWindow() -> bool {
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->GetWorkPos());
    ImGui::SetNextWindowSize(viewport->GetWorkSize());

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                    ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                    ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
                    ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0F);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{});
    bool show = ImGui::Begin("DockSpace Demo", nullptr, window_flags);
    ImGui::PopStyleVar(2);

    if (show) {
        InitDockingLayout();
        ImGui::DockSpace(ImGui::GetID(kDockspaceName.c_str()), {0, 0});
    }
    return show;
}

void ImageProcessorApplicationView::InitDockingLayout() {
    if (ImGui::DockBuilderGetNode(ImGui::GetID(kDockspaceName.c_str())) == nullptr) {
        ImGuiID dockspace_id = ImGui::GetID(kDockspaceName.c_str());
        ImGui::DockBuilderRemoveNode(dockspace_id);
        ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetWindowViewport()->Size);

        ImGuiID dock_main_id = dockspace_id;
        ImGuiID dock_left_id =
            ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.3f, nullptr, &dock_main_id);

        ImGui::DockBuilderDockWindow(kTextureProcessorsListView.c_str(), dock_left_id);
        ImGui::DockBuilderDockWindow(kImageViewWindowName.c_str(), dock_main_id);
        ImGui::DockBuilderFinish(dockspace_id);
    }
}

void ImageProcessorApplicationView::EndDockingWindow() { ImGui::End(); }

void ImageProcessorApplicationView::RenderMenuBar() {
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open", nullptr, false)) {
                file_dialog_view_.StartLoadingImage();
            }
            if (ImGui::MenuItem("Save", nullptr, false, file_dialog_view_.CanSaveImage())) {
                file_dialog_view_.StartSavingImage();
            }
            if (ImGui::MenuItem("Exit", nullptr, false)) {
                SetWantClose();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
}

}  // namespace image_processor::view
