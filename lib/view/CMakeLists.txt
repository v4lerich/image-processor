project(image-processor-view)

add_library(${PROJECT_NAME}
        view.h view.cc
        image_processor_view.h image_processor_view.cc
        file_dialog_view.h file_dialog_view.cc
        image_view.h image_view.cc)

add_library(image-processor::view
        ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
        PRIVATE icon-font-headers
        PUBLIC imgui imgui-filedialog image-processor::model)

target_include_directories(${PROJECT_NAME}
        PUBLIC .)
