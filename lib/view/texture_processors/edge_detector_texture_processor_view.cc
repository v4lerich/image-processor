#include "edge_detector_texture_processor_view.h"

#include <texture_processors/gl_texture_edge_detector_processor.h>

namespace image_processor::view::texture_processors {

struct EdgeDetectorInfo {
    std::string title;
    model::Kernel x_kernel;
    model::Kernel y_kernel;
};

static std::map<EdgeDetectorTextureProcessorView::EdgeDetectorType, EdgeDetectorInfo>
    kEdgeDetectorTypes = {{EdgeDetectorTextureProcessorView::EdgeDetectorType::kSobel,
                           EdgeDetectorInfo{.title = "Sobel",
                                            .x_kernel = model::Kernel{{
                                                {-1.0f, -2.0f, -1.0f},  //
                                                {+0.0f, +0.0f, +0.0f},  //
                                                {+1.0f, +2.0f, +1.0f},  //
                                            }},
                                            .y_kernel = model::Kernel{{
                                                {-1.0f, +0.0f, +1.0f},  //
                                                {-2.0f, +0.0f, +2.0f},  //
                                                {-1.0f, +0.0f, +1.0f},  //
                                            }}}},
                          {EdgeDetectorTextureProcessorView::EdgeDetectorType::kPrewitt,
                           EdgeDetectorInfo{.title = "Prewitt",
                                            .x_kernel = model::Kernel{{
                                                {-1.0f, -1.0f, -1.0f},  //
                                                {+0.0f, +0.0f, +0.0f},  //
                                                {+1.0f, +1.0f, +1.0f},  //
                                            }},
                                            .y_kernel = model::Kernel{{
                                                {-1.0f, +0.0f, +1.0f},  //
                                                {-1.0f, +0.0f, +1.0f},  //
                                                {-1.0f, +0.0f, +1.0f},  //
                                            }}}},
                          {EdgeDetectorTextureProcessorView::EdgeDetectorType::kScharr,
                           EdgeDetectorInfo{.title = "Scharr",
                                            .x_kernel = model::Kernel{{
                                                {-3.0f, -10.0f, -3.0f},  //
                                                {+0.0f, +0.0f, +0.0f},   //
                                                {+3.0f, +10.0f, +3.0f},  //
                                            }},
                                            .y_kernel = model::Kernel{{
                                                {-3.0f, +0.0f, +3.0f},    //
                                                {-10.0f, +0.0f, +10.0f},  //
                                                {-3.0f, +0.0f, +3.0f},    //
                                            }}}}

};

EdgeDetectorTextureProcessorView::EdgeDetectorTextureProcessorView(Factory& factory)
    : TextureProcessorView{factory} {}

void EdgeDetectorTextureProcessorView::RenderParameters() {
    bool changed = false;
    //    changed |= ImGui::InputInt("Half width", &half_width_, 1, 0);
    //    half_width_ = std::clamp(half_width_, 0, 10);
    //
    //    changed |= ImGui::InputInt("Half height", &half_height_, 1, 0);
    //    half_height_ = std::clamp(half_height_, 0, 10);

    const auto chosen_edge_detector = kEdgeDetectorTypes.find(edge_detector_type_)->second;
    if (ImGui::BeginCombo("Type", chosen_edge_detector.title.c_str())) {
        for (const auto& [type, edge_detector] : kEdgeDetectorTypes) {
            bool is_selected = type == edge_detector_type_;
            if (ImGui::Selectable(edge_detector.title.c_str(), &is_selected)) {
                edge_detector_type_ = type;
                changed |= true;
            }
            if (is_selected) ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    if (changed) SetChanged();
}  // namespace image_processor::view::texture_processors

auto EdgeDetectorTextureProcessorView::GetTitle() -> std::string { return "Edge detector filter"; }

auto EdgeDetectorTextureProcessorView::CreateTextureProcessor()
    -> std::unique_ptr<TextureProcessor> {
    const auto& chosen_edge_detector = kEdgeDetectorTypes[edge_detector_type_];
    return GetFactory().CreateEdgeDetectorTextureProcessor(chosen_edge_detector.x_kernel,
                                                           chosen_edge_detector.y_kernel);
}

}  // namespace image_processor::view::texture_processors
