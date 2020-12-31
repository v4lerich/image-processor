project(image-processor-view)

add_library(${PROJECT_NAME}
        view.h view.cc
        image_view.h image_view.cc
        file_dialog_view.h file_dialog_view.cc
        image_processor_application_view.h image_processor_application_view.cc

        texture_processors_list_view.h texture_processors_list_view.cc
        texture_processors/texture_processor_view.h texture_processors/texture_processor_view.cc
        texture_processors/median_texture_processor_view.h texture_processors/median_texture_processor_view.cc
        texture_processors/edge_detector_texture_processor_view.h texture_processors/edge_detector_texture_processor_view.cc
        texture_processors/kernel_texture_processor_view.h texture_processors/kernel_texture_processor_view.cc
        texture_processors/average_texture_processor_view.h texture_processors/average_texture_processor_view.cc
        )

add_library(image-processor::view
        ALIAS ${PROJECT_NAME})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
target_link_libraries(${PROJECT_NAME}
        PRIVATE icon-font-headers
        PUBLIC ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} imgui imgui-filedialog image-processor::model stdc++fs)

target_include_directories(${PROJECT_NAME}
        PUBLIC . ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})

