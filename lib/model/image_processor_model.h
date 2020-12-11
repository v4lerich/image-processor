#ifndef IMAGEPROCESSOR_IMAGE_PROCESSOR_MODEL_H
#define IMAGEPROCESSOR_IMAGE_PROCESSOR_MODEL_H

#include <glad/gl.h>

namespace image_processor::model {

class ImageProcessorModel {
  public:
    ImageProcessorModel();

    GLuint initial_texture_id;
};

}  // namespace image_processor::model

#endif  // IMAGEPROCESSOR_IMAGE_PROCESSOR_MODEL_H
