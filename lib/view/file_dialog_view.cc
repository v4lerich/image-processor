#include "file_dialog_view.h"

#include <ImGuiFileDialog.h>
#include <SDL.h>
#include <SDL_image.h>
#include <backends/imgui_impl_opengl3.h>
#include <glad/gl.h>
#include <imgui.h>

#include <string>

namespace image_processor::view {

static const std::string kSaveDialogWindowName = "save_dialog";
static const std::string kSaveErrorDialogWindowName = "Save error";
static const std::string kOpenDialogWindowName = "open_dialog";
static const std::string kOpenErrorDialogWindowName = "Open error";
static const std::string kImageFilters =
    "Image files (*.png *.gif *.jpg *.jpeg){.png,.gif,.jpg,.jpeg}";

FileDialogView::FileDialogView(Model& model) : model_(model) {}

void FileDialogView::Render() { RenderLoadingImageDialog(); }

void FileDialogView::StartSavingImage() { is_saving_ = true; }

void FileDialogView::StartLoadingImage() { is_loading_ = true; }

void FileDialogView::RenderSavingImageDialog() {}

void FileDialogView::RenderLoadingImageDialog() {
    auto igfd_instance = igfd::ImGuiFileDialog::Instance();

    if (is_loading_) {
        igfd_instance->OpenDialog(kOpenDialogWindowName, "Open File", kImageFilters.c_str(), ".",
                                  "recording");
    }

    if (igfd_instance->FileDialog(kOpenDialogWindowName, ImGuiWindowFlags_NoCollapse,
                                  ImVec2{0, 300})) {
        is_loading_ = false;
        if (igfd_instance->IsOk) {
            if (auto image = IMG_Load(igfd_instance->GetFilePathName().c_str()); image != nullptr) {
                StoreImage(image);
                SDL_FreeSurface(image);
            } else {
                ImGui::OpenPopup(kOpenErrorDialogWindowName.c_str());
            }
        }
        igfd_instance->CloseDialog(kOpenDialogWindowName);
    }

    bool error_dialog_open = true;
    if (ImGui::BeginPopupModal("Modal window", &error_dialog_open)) {
        const auto error = IMG_GetError();
        ImGui::Text("%s", error);
        if (ImGui::Button("Ok")) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void FileDialogView::StoreImage(SDL_Surface* image) {
    GLuint image_texture;
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    SDL_Surface* formatted_image;
    formatted_image = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_RGBA32, 0);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, formatted_image->w, formatted_image->h, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, formatted_image->pixels);

    model::GlTexture texture{image_texture, formatted_image->w, formatted_image->h};
    model_.SetInitialTexture(std::move(texture));

    SDL_FreeSurface(formatted_image);
}

}  // namespace image_processor::view
