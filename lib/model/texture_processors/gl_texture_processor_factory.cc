#include "gl_texture_processor_factory.h"

#include "gl_texture_average_processor.h"
#include "gl_texture_edge_detector_processor.h"
#include "gl_texture_kernel_processor.h"
#include "gl_texture_median_processor.h"

namespace image_processor::model::texture_processors {

auto GlTextureProcessorFactory::CreateMedianTextureProcessor(unsigned int half_width,
                                                             unsigned int half_height)
    -> std::unique_ptr<GlTextureProcessor> {
    const auto size = std::make_pair(half_width, half_height);
    auto it = median_shader_programs_.find(size);
    if (it == std::end(median_shader_programs_)) {
        it = median_shader_programs_
                 .emplace(size, shader_programs::GlMedianShaderProgram(half_width, half_height))
                 .first;
    }

    const auto& program = it->second;
    return std::make_unique<GlTextureMedianProcessor>(program);
}

auto GlTextureProcessorFactory::CreateAverageTextureProcessor(unsigned int half_width,
                                                              unsigned int half_height)
    -> std::unique_ptr<GlTextureProcessor> {
    return std::make_unique<GlTextureAverageProcessor>(average_program_, half_width, half_height);
}

auto GlTextureProcessorFactory::CreateEdgeDetectorTextureProcessor(const Kernel& x_kernel,
                                                                   const Kernel& y_kernel)
    -> std::unique_ptr<GlTextureProcessor> {
    return std::make_unique<GlTextureEdgeDetectorProcessor>(edge_detector_program_, x_kernel,
                                                            y_kernel);
}

auto GlTextureProcessorFactory::CreateKernelTextureProcessor(const Kernel& kernel)
    -> std::unique_ptr<GlTextureProcessor> {
    return std::make_unique<GlTextureKernelProcessor>(kernel_based_program_, kernel);
}

}  // namespace image_processor::model::texture_processors
