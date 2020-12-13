#ifndef IMAGEPROCESSOR_KERNEL_H
#define IMAGEPROCESSOR_KERNEL_H

#include <array>
#include <cstdlib>
#include <vector>

namespace image_processor::model {

class Kernel final {
  public:
    using Coefficient = float;
    using Index = ssize_t;
    template <class T, size_t WIDTH, size_t HEIGHT>
    using Array2D = std::array<std::array<T, WIDTH>, HEIGHT>;

    Kernel(size_t offset_width, size_t offset_height);

    template <class T, size_t OFFSET_WIDTH, size_t OFFSET_HEIGHT>
    Kernel(const Array2D<T, 2 * OFFSET_WIDTH + 1, 2 * OFFSET_HEIGHT + 1>& coefficients)
        : offset_width_{OFFSET_WIDTH}, offset_height_{OFFSET_HEIGHT} {
        for (const auto& row : coefficients) {
            coefficients_.insert(end(coefficients_), begin(row), end(row));
        }
    }

    auto GetCoefficient(Index delta_width, Index delta_height) -> Coefficient;
    void SetCoefficient(Index delta_width, Index delta_height, Coefficient coefficient);

    auto GetOffsetWidth() const -> size_t { return offset_width_; }
    auto GetOffsetHeight() const -> size_t { return offset_height_; }

    auto GetWidth() const -> size_t { return offset_width_ * 2 + 1; }
    auto GetHeight() const -> size_t { return offset_height_ * 2 + 1; }

    auto GetData() const -> const Coefficient* { return coefficients_; }

  private:
    auto EncodeIndex(Index delta_width, Index delta_height) const -> Index;

    size_t offset_width_;
    size_t offset_height_;
    std::vector<Coefficient> coefficients_;
};

}  // namespace image_processor::model

#endif  // IMAGEPROCESSOR_KERNEL_H
