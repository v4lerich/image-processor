#include "gl_texture_processor_factory.h"

#include "gl_texture_average_processor.h"
#include "gl_texture_edge_detector_processor.h"
#include "gl_texture_kernel_processor.h"
#include "gl_texture_median_processor.h"

namespace image_processor::model::texture_processors {

auto GlTextureProcessorFactory::CreateMedianTextureProcessor(unsigned int half_width,
                                                             unsigned int half_height)
    -> std::unique_ptr<GlTextureProcessor> {
    return std::make_unique<GlTextureMedianProcessor>(median_shader_program_, half_width,
                                                      half_height);
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
