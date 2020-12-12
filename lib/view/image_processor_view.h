#ifndef IMAGEPROCESSOR_IMAGE_PROCESSOR_VIEW_H
#define IMAGEPROCESSOR_IMAGE_PROCESSOR_VIEW_H

#include <image_processor_model.h>

#include "file_dialog_view.h"
#include "image_view.h"
#include "view.h"

namespace image_processor::view {

class ImageProcessorView final : public View {
  public:
    using Model = model::ImageProcessorModel;

    ImageProcessorView(Model& model);
    void Render() override;
    bool BeginDockingWindow();
    void EndDockingWindow();
    void InitDockingLayout();
    void RenderMenuBar();

  private:
    ImageView image_view_;
    FileDialogView file_dialog_view_;
};

}  // namespace image_processor::view

#endif  // IMAGEPROCESSOR_IMAGE_PROCESSOR_VIEW_H
