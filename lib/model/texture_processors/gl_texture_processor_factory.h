#ifndef IMAGEPROCESSOR_GL_TEXTURE_PROCESSOR_FACTORY_H
#define IMAGEPROCESSOR_GL_TEXTURE_PROCESSOR_FACTORY_H

#include <map>

#include "gl_texture_processor.h"
#include "shader_programs/gl_average_shader_program.h"
#include "shader_programs/gl_edge_detector_shader_program.h"
#include "shader_programs/gl_kernel_based_shader_program.h"
#include "shader_programs/gl_median_shader_program.h"

namespace image_processor::model::texture_processors {

class GlTextureProcessorFactory {
  public:
    GlTextureProcessorFactory() = default;

    auto CreateMedianTextureProcessor(unsigned int half_width, unsigned int half_height)
        -> std::unique_ptr<GlTextureProcessor>;

    auto CreateAverageTextureProcessor(unsigned int half_width, unsigned int half_height)
        -> std::unique_ptr<GlTextureProcessor>;

    auto CreateEdgeDetectorTextureProcessor(const Kernel& x_kernel, const Kernel& y_kernel)
        -> std::unique_ptr<GlTextureProcessor>;

    auto CreateKernelTextureProcessor(const Kernel& kernel) -> std::unique_ptr<GlTextureProcessor>;

  private:
    shader_programs::GlMedianShaderProgram median_shader_program_{};
    shader_programs::GlKernelBasedShaderProgram kernel_based_program_{};
    shader_programs::GlAverageShaderProgram average_program_{};
    shader_programs::GlEdgeDetectorShaderProgram edge_detector_program_{};
};

}  // namespace image_processor::model::texture_processors

#endif  // IMAGEPROCESSOR_GL_TEXTURE_PROCESSOR_FACTORY_H
