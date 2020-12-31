#include <image_processor_application_view.h>
#include <image_processor_model.h>

#include <memory>

#include "application.h"

namespace view = image_processor::view;
namespace model = image_processor::model;

auto main(int argc, char **argv) -> int {
    image_processor::Application application{argc, argv};

    auto return_code = application.Init();
    if (return_code != 0) {
        return return_code;
    }

    model::ImageProcessorModel model{};
    auto image_processor = std::make_unique<view::ImageProcessorApplicationView>(model);
    application.AddView(std::move(image_processor));

    return_code = application.Run();
    return return_code;
}