#ifndef IMAGEPROCESSOR_FILE_DIALOG_VIEW_H
#define IMAGEPROCESSOR_FILE_DIALOG_VIEW_H

#include <SDL.h>
#include <image_processor_model.h>

#include <filesystem>

#include "view.h"

namespace image_processor::view {

class FileDialogView final : public View {
  public:
    using Model = model::ImageProcessorModel;
    explicit FileDialogView(Model& model);

    void StartSavingImage();
    void StartLoadingImage();

    auto CanSaveImage() -> bool;

  protected:
    void RenderIndexed() override;

  private:
    void RenderSavingImageDialog();
    void RenderLoadingImageDialog();
    void RenderErrorDialog();
    void SaveImage();

    model::GlTexture LoadGlImage(SDL_Surface* image);
    SDL_Surface* StoreGlImage(const model::GlTexture& texture);

    Model& model_;

    bool is_saving_{};
    bool is_loading_{};
    std::filesystem::path file_path_{};
    std::string error_message_{};
};

}  // namespace image_processor::view

#endif  // IMAGEPROCESSOR_FILE_DIALOG_VIEW_H
