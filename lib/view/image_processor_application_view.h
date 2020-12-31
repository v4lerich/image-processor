#ifndef IMAGEPROCESSOR_IMAGE_PROCESSOR_APPLICATION_VIEW_H
#define IMAGEPROCESSOR_IMAGE_PROCESSOR_APPLICATION_VIEW_H

#include <image_processor_model.h>

#include "file_dialog_view.h"
#include "image_view.h"
#include "texture_processors_list_view.h"
#include "view.h"

namespace image_processor::view {

class ImageProcessorApplicationView final : public View {
  public:
    using Model = model::ImageProcessorModel;

    explicit ImageProcessorApplicationView(Model& model);
    bool BeginDockingWindow();
    void EndDockingWindow();
    void InitDockingLayout();
    void RenderMenuBar();

  protected:
    void RenderIndexed() override;

  private:
    ImageView image_view_;
    TextureProcessorsListView texture_processors_list_view_;
    FileDialogView file_dialog_view_;
};

}  // namespace image_processor::view

#endif  // IMAGEPROCESSOR_IMAGE_PROCESSOR_APPLICATION_VIEW_H
