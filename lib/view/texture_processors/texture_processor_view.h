#ifndef IMAGEPROCESSOR_TEXTURE_PROCESSOR_VIEW_H
#define IMAGEPROCESSOR_TEXTURE_PROCESSOR_VIEW_H

#include <imgui.h>
#include <texture_processors/gl_texture_processor.h>
#include <texture_processors/gl_texture_processor_factory.h>

#include "view.h"

namespace image_processor::view::texture_processors {

class TextureProcessorView : public View {
  public:
    using Factory = model::texture_processors::GlTextureProcessorFactory;
    using TextureProcessor = model::texture_processors::GlTextureProcessor;

    explicit TextureProcessorView(Factory& factory);

    auto Changed() -> bool;
    auto WantMoveUp() -> bool;
    auto WantMoveDown() -> bool;
    virtual auto CreateTextureProcessor() -> std::unique_ptr<TextureProcessor> = 0;

  protected:
    auto GetFactory() -> Factory&;

    void SetChanged();
    void RenderIndexed() override;
    virtual void RenderParameters() = 0;
    virtual auto GetTitle() -> std::string = 0;

  private:
    Factory& factory_;
    bool changed_{};
    bool want_move_up_{};
    bool want_move_down_{};
};

}  // namespace image_processor::view::texture_processors

#endif  // IMAGEPROCESSOR_TEXTURE_PROCESSOR_VIEW_H
