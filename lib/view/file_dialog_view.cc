#include "file_dialog_view.h"

#include <ImGuiFileDialog.h>
#include <imgui.h>

#include <string>

namespace image_processor::view {

static const std::string kSaveDialogWindowName = "save_dialog";
static const std::string kOpenDialogWindowName = "open_dialog";
static const std::string kImageFilters = "Image files (*.png *.gif *.jpg *.jpeg){.png,.gif,.jpg,.jpeg}";

FileDialogView::FileDialogView() {}

void FileDialogView::Render() { RenderLoadingImageDialog(); }

void FileDialogView::StartSavingImage() { is_saving_ = true; }

void FileDialogView::StartLoadingImage() { is_loading_ = true; }

void FileDialogView::RenderSavingImageDialog() {}

void FileDialogView::RenderLoadingImageDialog() {
    auto igfd_instance = igfd::ImGuiFileDialog::Instance();

    if (is_loading_) {
        igfd_instance->OpenDialog(kOpenDialogWindowName, "Open File", kImageFilters.c_str(),
                                 ".", "recording");
    }

    if (igfd_instance->FileDialog(kOpenDialogWindowName, ImGuiWindowFlags_NoCollapse,
                                  ImVec2{0, 300})) {
        is_loading_ = false;
        if (igfd_instance->IsOk) {
        }
        igfd_instance->CloseDialog(kOpenDialogWindowName);
    }
}

}  // namespace image_processor::view
