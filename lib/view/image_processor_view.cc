#include "image_processor_view.h"

#include <imgui.h>
#include <imgui_internal.h>

#include <string>

namespace image_processor::view {

const std::string kDockspaceName = "main_dockspace";
const std::string kImageViewWindowName = "image_view";

ImageProcessorView::ImageProcessorView(ImageProcessorView::Model& model)
    : image_view_{kImageViewWindowName, model}, file_dialog_view_{model} {}

void ImageProcessorView::Render() {
    if (BeginDockingWindow()) {
        RenderMenuBar();

        ImGuiWindowClass window_class;
        window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar;

        ImGui::SetNextWindowClass(&window_class);
        image_view_.Render();

        file_dialog_view_.Render();

        EndDockingWindow();
    }
}

auto ImageProcessorView::BeginDockingWindow() -> bool {
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

    if (ImGui::Begin("DockSpace Demo", nullptr, window_flags)) {
        ImGui::PopStyleVar();

        InitDockingLayout();
        ImGui::DockSpace(ImGui::GetID(kDockspaceName.c_str()), {0, 0});
        return true;
    }
    ImGui::PopStyleVar();
    return false;
}

void ImageProcessorView::InitDockingLayout() {
    if (ImGui::DockBuilderGetNode(ImGui::GetID(kDockspaceName.c_str())) == nullptr) {
        ImGuiID dockspace_id = ImGui::GetID(kDockspaceName.c_str());
        ImGui::DockBuilderRemoveNode(dockspace_id);
        ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetWindowViewport()->Size);

        ImGuiID dock_main_id = dockspace_id;
        ImGuiID dock_left_id =
            ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0, nullptr, &dock_main_id);

        //        ImGui::DockBuilderDockWindow(player_view_.WindowName().c_str(), dock_up_id);
        ImGui::DockBuilderDockWindow(kImageViewWindowName.c_str(), dock_main_id);
        ImGui::DockBuilderFinish(dockspace_id);
    }
}

void ImageProcessorView::EndDockingWindow() {
    ImGui::End();
    ImGui::PopStyleVar();
}

void ImageProcessorView::RenderMenuBar() {
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
