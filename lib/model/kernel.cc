#include "kernel.h"

namespace image_processor::model {

Kernel::Kernel(size_t offset_width, size_t offset_height)
    : offset_width_{offset_width_}, offset_height_{offset_height_} {
    coefficients_.resize(offset_height * 2);
    for (auto& row : coefficients_) {
        row.resize(offset_width * 2);
    }
}

Kernel::Coefficient Kernel::GetCoefficient(Kernel::Index delta_width, Kernel::Index delta_height) {
    return coefficients_[offset_height_ + delta_height][offset_width_ + delta_width];
}

void Kernel::SetCoefficient(Kernel::Index delta_width, Kernel::Index delta_height,
                            Kernel::Coefficient coefficient) {
    coefficients_[offset_height_ + delta_height][offset_width_ + delta_width] = coefficient;
}

}  // namespace image_processor::model
