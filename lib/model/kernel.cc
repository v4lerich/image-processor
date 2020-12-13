#include "kernel.h"

namespace image_processor::model {

Kernel::Kernel(size_t offset_width, size_t offset_height)
    : offset_width_{offset_width_},
      offset_height_{offset_height_},
      coefficients_((offset_width * 2 + 1) * (offset_height * 2 + 1)) {}

Kernel::Coefficient Kernel::GetCoefficient(Index delta_width, Index delta_height) {
    const auto index = EncodeIndex(delta_width, delta_height);
    return coefficients_[index];
}

void Kernel::SetCoefficient(Index delta_width, Index delta_height, Coefficient coefficient) {
    const auto index = EncodeIndex(delta_width, delta_height);
    coefficients_[index] = coefficient;
}

auto Kernel::EncodeIndex(Kernel::Index delta_width, Kernel::Index delta_height) const
    -> Kernel::Index {
    Index width_index = delta_width + GetWidth();
    Index height_index = delta_height + GetHeight();
    return GetWidth() * height_index + width_index;
}

}  // namespace image_processor::model
