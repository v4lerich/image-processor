#include "file_dialog_view.h"

#include <ImGuiFileDialog.h>
#include <SDL.h>
#include <SDL_image.h>
#include <backends/imgui_impl_opengl3.h>
#include <glad/gl.h>
#include <imgui.h>

#include <algorithm>
#include <filesystem>
#include <string>

namespace image_processor::view {

static const std::string kErrorDialogWindowName = "Error";

static const std::string kSaveDialogWindowName = "save_dialog";
static const std::string kSavePromptDialogWindowName = "File exists";
static const std::string kSavePromptFormat =
    "File already exists: %s.\n Do you want to overwrite it?";
static const std::string kSaveImageFilters = ".png,.jpg,.jpeg";

static const std::string kOpenDialogWindowName = "open_dialog";
static const std::string kOpenErrorDialogWindowName = "Open error";
static const std::string kOpenImageFilters = "Image files (*.png *.jpg *.jpeg){.png,.jpg,.jpeg}";

FileDialogView::FileDialogView(Model& model) : model_(model) {}

void FileDialogView::Render() {
    RenderLoadingImageDialog();
    RenderSavingImageDialog();
    RenderErrorDialog();
}

void FileDialogView::StartSavingImage() {
    auto igfd_instance = igfd::ImGuiFileDialog::Instance();
    igfd_instance->OpenDialog(kSaveDialogWindowName, "Save File", kSaveImageFilters.c_str(), ".",
                              "");
}

void FileDialogView::StartLoadingImage() { is_loading_ = true; }

void FileDialogView::RenderSavingImageDialog() {
    auto igfd_instance = igfd::ImGuiFileDialog::Instance();

    ImGuiWindowFlags window_flags(ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking);
    if (igfd_instance->FileDialog(kSaveDialogWindowName, window_flags, ImVec2{0, 300})) {
        is_saving_ = false;
        if (igfd_instance->IsOk) {
            file_path_ = igfd_instance->GetFilePathName().c_str();
            if (std::filesystem::exists(file_path_)) {
                ImGui::OpenPopup(kSavePromptDialogWindowName.c_str());
            } else {
                SaveImage();
            }
        }
        igfd_instance->CloseDialog(kSaveDialogWindowName);
    }

    bool prompt_dialog_open = true;
    if (ImGui::BeginPopupModal(kSavePromptDialogWindowName.c_str(), &prompt_dialog_open)) {
        ImGui::Text(kSavePromptFormat.c_str(), file_path_.c_str());
        if (ImGui::Button("Yes")) {
            SaveImage();
            ImGui::CloseCurrentPopup();
        }
        if (ImGui::Button("No")) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void FileDialogView::SaveImage() {
    SDL_Surface* image = StoreGlImage(model_.GetInitialTexture().value());

    auto extension = file_path_.extension().string();
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    int return_code = 0;
    if (extension == ".jpeg" || extension == ".jpg") {
        return_code = IMG_SaveJPG(image, file_path_.string().c_str(), 100);
    } else if (extension == ".png") {
        return_code = IMG_SavePNG(image, file_path_.string().c_str());
    }

    if (return_code != 0) {
        error_message_ = IMG_GetError();
        ImGui::OpenPopup(kErrorDialogWindowName.c_str());
    }

    SDL_FreeSurface(image);
}

void FileDialogView::RenderLoadingImageDialog() {
    auto igfd_instance = igfd::ImGuiFileDialog::Instance();

    if (is_loading_) {
        igfd_instance->OpenDialog(kOpenDialogWindowName, "Open File", kOpenImageFilters.c_str(),
                                  ".", "recording");
    }

    ImGuiWindowFlags window_flags(ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking);
    if (igfd_instance->FileDialog(kOpenDialogWindowName, window_flags, ImVec2{0, 300})) {
        is_loading_ = false;
        if (igfd_instance->IsOk) {
            if (auto image = IMG_Load(igfd_instance->GetFilePathName().c_str()); image != nullptr) {
                auto gl_image = LoadGlImage(image);
                model_.SetInitialTexture(std::move(gl_image));
                SDL_FreeSurface(image);
            } else {
                ImGui::OpenPopup(kOpenErrorDialogWindowName.c_str());
            }
        }
        igfd_instance->CloseDialog(kOpenDialogWindowName);
    }

    bool error_dialog_open = true;
    if (ImGui::BeginPopupModal(kOpenErrorDialogWindowName.c_str(), &error_dialog_open)) {
        const auto error = IMG_GetError();
        ImGui::Text("%s", error);
        if (ImGui::Button("Ok")) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

model::GlTexture FileDialogView::LoadGlImage(SDL_Surface* image) {
    GLuint image_texture;
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    SDL_Surface* formatted_image;
    formatted_image = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_RGBA32, 0);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, formatted_image->w, formatted_image->h, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, formatted_image->pixels);

    model::GlTexture texture{image_texture, formatted_image->w, formatted_image->h};

    SDL_FreeSurface(formatted_image);
    return texture;
}

void FileDialogView::RenderErrorDialog() {
    bool error_dialog_open = true;
    if (ImGui::BeginPopupModal(kErrorDialogWindowName.c_str(), &error_dialog_open)) {
        ImGui::Text("%s", error_message_.c_str());
        if (ImGui::Button("Ok")) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

SDL_Surface* FileDialogView::StoreGlImage(const model::GlTexture& texture) {
    auto image = SDL_CreateRGBSurfaceWithFormat(0, texture.width, texture.height, 32,
                                                SDL_PIXELFORMAT_RGBA32);

    SDL_LockSurface(image);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
    SDL_UnlockSurface(image);
    return image;
}

auto FileDialogView::CanSaveImage() -> bool { return model_.GetInitialTexture().has_value(); }

}  // namespace image_processor::view
