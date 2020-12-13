#ifndef IMAGEPROCESSOR_KERNEL_H
#define IMAGEPROCESSOR_KERNEL_H

#include <array>
#include <cstdlib>
#include <vector>

namespace image_processor::model {

class Kernel final {
  public:
    using Coefficient = double;
    using Index = ssize_t;
    template <class T, size_t WIDTH, size_t HEIGHT>
    using Array2D = std::array<std::array<T, WIDTH>, HEIGHT>;

    Kernel(size_t offset_width, size_t offset_height);

    template <class T, size_t OFFSET_WIDTH, size_t OFFSET_HEIGHT>
    Kernel(const Array2D<T, 2 * OFFSET_WIDTH + 1, 2 * OFFSET_HEIGHT + 1>& coefficients)
        : offset_width_{OFFSET_WIDTH}, offset_height_{OFFSET_HEIGHT} {
        for (const auto &row : coefficients) {
            std::vector<Coefficient> coefficients_row(begin(row), end(row));
            coefficients_.push_back(std::move(coefficients_row));
        }
    }

    Coefficient GetCoefficient(Index delta_width, Index delta_height);
    void SetCoefficient(Index delta_width, Index delta_height, Coefficient coefficient);

    auto GetOffsetWidth() const -> size_t { return offset_width_; };
    auto GetOffsetHeight() const -> size_t { return offset_height_; };

  private:
    template <class T>
    using Vector2D = std::vector<std::vector<T>>;

    size_t offset_width_;
    size_t offset_height_;
    Vector2D<Coefficient> coefficients_;
};

}  // namespace image_processor::model

#endif  // IMAGEPROCESSOR_KERNEL_H
