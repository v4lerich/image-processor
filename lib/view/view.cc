#include "view.h"

namespace image_processor::view {

auto View::WantClose() -> bool { return want_close_; }

void View::SetWantClose() { want_close_ = true; }

}  // namespace image_processor::view
