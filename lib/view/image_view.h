#ifndef IMAGEPROCESSOR_IMAGE_VIEW_H
#define IMAGEPROCESSOR_IMAGE_VIEW_H

#include "view.h"

namespace image_processor::view {

class ImageView final : public View {
  public:
    ImageView();
    void Render() override;

  private:
};

}  // namespace image_processor::view

#endif  // IMAGEPROCESSOR_IMAGE_VIEW_H
