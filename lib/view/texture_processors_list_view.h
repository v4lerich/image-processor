#ifndef IMAGEPROCESSOR_TEXTURE_PROCESSORS_LIST_VIEW_H
#define IMAGEPROCESSOR_TEXTURE_PROCESSORS_LIST_VIEW_H

#include <image_processor_model.h>

#include <memory>
#include <string>
#include <vector>

#include "texture_processors/texture_processor_view.h"
#include "view.h"

namespace image_processor::view {

class TextureProcessorsListView : public View {
  public:
    using Model = model::ImageProcessorModel;
    using ItemView = texture_processors::TextureProcessorView;

    explicit TextureProcessorsListView(Model& model, std::string windowName);

  protected:
    void RenderIndexed() override;
    void RenderFactoryPopup();

  private:
    void ProcessImageProcessors();
    void Append(std::unique_ptr<ItemView> image_processor_view);

    Model& model_;

    bool show_factory_popup_{};
    unsigned int factory_index_{0};
    std::string window_name_;
    std::vector<std::unique_ptr<ItemView>> image_processor_views_{};
    void UpdateTextureProcessors() const;
};

}  // namespace image_processor::view

#endif  // IMAGEPROCESSOR_TEXTURE_PROCESSORS_LIST_VIEW_H
