#include <image_processor_view.h>

#include <memory>

#include "application.h"

namespace view = image_processor::view;

auto main(int argc, char **argv) -> int {
    image_processor::Application application{argc, argv};

    auto return_code = application.Init();
    if (return_code != 0) {
        return return_code;
    }

    auto image_processor = std::make_unique<view::ImageProcessorView>();
    application.AddView(std::move(image_processor));

    return_code = application.Run();
    return return_code;
}