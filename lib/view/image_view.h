#ifndef IMAGEPROCESSOR_IMAGE_VIEW_H
#define IMAGEPROCESSOR_IMAGE_VIEW_H

#include <image_processor_model.h>

#include "view.h"

namespace image_processor::view {

class ImageView final : public View {
  public:
    using Model = model::ImageProcessorModel;

    ImageView(std::string window_name, Model& model);
    void Render() override;

  private:
    Model& model_;
    const std::string window_name_;
};

}  // namespace image_processor::view

#endif  // IMAGEPROCESSOR_IMAGE_VIEW_H
