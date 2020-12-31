#ifndef IMAGEPROCESSOR_IMAGE_PROCESSOR_MODEL_H
#define IMAGEPROCESSOR_IMAGE_PROCESSOR_MODEL_H

#include <optional>

#include "gl_texture.h"
#include "shader_programs/gl_average_shader_program.h"
#include "shader_programs/gl_edge_detector_shader_program.h"
#include "shader_programs/gl_kernel_based_shader_program.h"
#include "texture_processors/gl_texture_processor_factory.h"

namespace image_processor::model {

class ImageProcessorModel final {
  public:
    using GlTextureProcessorPtr = std::unique_ptr<texture_processors::GlTextureProcessor>;

    ImageProcessorModel();

    auto GetInitialTexture() const -> const std::optional<GlTexture>&;
    auto GetResultTexture() const -> const std::optional<GlTexture>&;
    void SetInitialTexture(GlTexture texture);
    void ProcessTexture();

    auto GetTextureProcessorFactory() -> texture_processors::GlTextureProcessorFactory&;

    template <typename Iterator>
    requires std::same_as<typename std::iterator_traits<Iterator>::value_type,
                          GlTextureProcessorPtr> void
    SetImageProcessors(Iterator from, Iterator to) {
        texture_processors_.clear();
        for (auto it = from; it != to; ++it) {
            auto& texture_processor = *it;
            texture_processors_.emplace_back(std::move(texture_processor));
        }

        ProcessTexture();
    }

  private:
    std::optional<GlTexture> initial_texture_{};
    std::optional<GlTexture> result_texture_{};
    std::vector<GlTextureProcessorPtr> texture_processors_{};
    texture_processors::GlTextureProcessorFactory texture_processor_factory_;
};

}  // namespace image_processor::model

#endif  // IMAGEPROCESSOR_IMAGE_PROCESSOR_MODEL_H
