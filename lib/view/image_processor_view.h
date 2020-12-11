#ifndef IMAGEPROCESSOR_IMAGE_PROCESSOR_VIEW_H
#define IMAGEPROCESSOR_IMAGE_PROCESSOR_VIEW_H

#include "view.h"

namespace image_processor::view {

class ImageProcessorView final : public View {
  public:
    ImageProcessorView();
    void Render() override;
    bool BeginDockingWindow();
    void EndDockingWindow();
    void InitDockingLayout();
    void RenderMenuBar();
};

}  // namespace image_procoessor::view

#endif  // IMAGEPROCESSOR_IMAGE_PROCESSOR_VIEW_H
