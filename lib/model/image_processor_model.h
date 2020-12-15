#ifndef IMAGEPROCESSOR_IMAGE_PROCESSOR_MODEL_H
#define IMAGEPROCESSOR_IMAGE_PROCESSOR_MODEL_H

#include <glad/gl.h>

#include <optional>

#include "gl_texture.h"
#include "shader_programs/gl_average_shader_program.h"
#include "shader_programs/gl_kernel_based_shader_program.h"

namespace image_processor::model {

class ImageProcessorModel final {
  public:
    ImageProcessorModel();

    [[nodiscard]] auto GetInitialTexture() const -> const std::optional<GlTexture>&;
    void SetInitialTexture(GlTexture texture);

  private:
    std::optional<GlTexture> initial_texture_{};
    shader_programs::GlKernelBasedShaderProgram kernel_based_program_{};
    shader_programs::GlAverageShaderProgram average_program_{};
};

}  // namespace image_processor::model

#endif  // IMAGEPROCESSOR_IMAGE_PROCESSOR_MODEL_H
