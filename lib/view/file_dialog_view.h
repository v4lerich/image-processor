#ifndef IMAGEPROCESSOR_FILE_DIALOG_VIEW_H
#define IMAGEPROCESSOR_FILE_DIALOG_VIEW_H

#include <SDL.h>
#include <image_processor_model.h>

#include "view.h"

namespace image_processor::view {

class FileDialogView final : public View {
  public:
    using Model = model::ImageProcessorModel;
    explicit FileDialogView(Model& model);

    void Render() override;

    void StartSavingImage();
    void StartLoadingImage();

  private:
    void RenderSavingImageDialog();
    void RenderLoadingImageDialog();
    void StoreImage(SDL_Surface* image);

    Model& model_;
    bool is_saving_{};
    bool is_loading_{};
};

}  // namespace image_processor::view

#endif  // IMAGEPROCESSOR_FILE_DIALOG_VIEW_H
