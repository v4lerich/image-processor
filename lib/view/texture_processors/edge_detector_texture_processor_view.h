#ifndef IMAGEPROCESSOR_EDGE_DETECTOR_TEXTURE_PROCESSOR_VIEW_H
#define IMAGEPROCESSOR_EDGE_DETECTOR_TEXTURE_PROCESSOR_VIEW_H

#include <image_processor_model.h>

#include "texture_processor_view.h"

namespace image_processor::view::texture_processors {

class EdgeDetectorTextureProcessorView final : public TextureProcessorView {
  public:
    enum class EdgeDetectorType {
        kSobel,
        kScharr,
        kPrewitt,
    };

    explicit EdgeDetectorTextureProcessorView(Factory& factory);

  protected:
    void RenderParameters() override;
    auto GetTitle() -> std::string override;
    auto CreateTextureProcessor() -> std::unique_ptr<TextureProcessor> override;

  private:
    EdgeDetectorType edge_detector_type_{};
};

}  // namespace image_processor::view::texture_processors

#endif  // IMAGEPROCESSOR_EDGE_DETECTOR_TEXTURE_PROCESSOR_VIEW_H
