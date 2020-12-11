#ifndef IMAGEPROCESSOR_FILE_DIALOG_VIEW_H
#define IMAGEPROCESSOR_FILE_DIALOG_VIEW_H

#include "view.h"

namespace image_processor::view {

class FileDialogView final : public View {
  public:
    FileDialogView();

    void Render() override;

    void StartSavingImage();
    void StartLoadingImage();

  private:
    void RenderSavingImageDialog();
    void RenderLoadingImageDialog();

    bool is_saving_{};
    bool is_loading_{};
};

}  // namespace image_processor::view

#endif  // IMAGEPROCESSOR_FILE_DIALOG_VIEW_H
