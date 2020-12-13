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
    template <class T>
    using Vector2D = std::vector<std::vector<T>>;

    Kernel(size_t offset_width, size_t offset_height);

    Kernel(const Vector2D<Coefficient>& coefficients) {
        offset_height_ = coefficients.size() / 2;
        offset_width_ = coefficients.front().size() / 2;
        for (const auto& row : coefficients) {
            coefficients_.insert(end(coefficients_), begin(row), end(row));
        }
    }

    template <class T, size_t WIDTH, size_t HEIGHT>
    Kernel(const Array2D<T, WIDTH, HEIGHT>& coefficients)
        : offset_width_{WIDTH / 2}, offset_height_{HEIGHT / 2} {
        static_assert(WIDTH % 2 == 1 && HEIGHT % 2 == 1, "Size must be odd");
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

    auto GetData() const -> const Coefficient* { return coefficients_.data(); }

  private:
    auto EncodeIndex(Index delta_width, Index delta_height) const -> Index;

    size_t offset_width_;
    size_t offset_height_;
    std::vector<Coefficient> coefficients_;
};

}  // namespace image_processor::model

#endif  // IMAGEPROCESSOR_KERNEL_H
