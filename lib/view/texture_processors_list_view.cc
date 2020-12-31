#include "texture_processors_list_view.h"

#include <texture_processors/average_texture_processor_view.h>
#include <texture_processors/edge_detector_texture_processor_view.h>
#include <texture_processors/gl_texture_processor_factory.h>
#include <texture_processors/kernel_texture_processor_view.h>
#include <texture_processors/median_texture_processor_view.h>

#include <algorithm>

namespace image_processor::view {

struct TextureProcessorFactoryView {
    std::string title;
    std::function<std::unique_ptr<texture_processors::TextureProcessorView>(
        model::texture_processors::GlTextureProcessorFactory& factory)>
        factory_method;
};

static const std::vector<TextureProcessorFactoryView> kTextureProcessorFactoryViews = {
    {"Median filter",
     [](model::texture_processors::GlTextureProcessorFactory& factory) {
         return std::make_unique<texture_processors::MedianTextureProcessorView>(factory);
     }},
    {"Average filter",
     [](model::texture_processors::GlTextureProcessorFactory& factory) {
         return std::make_unique<texture_processors::AverageTextureProcessorView>(factory);
     }},
    {"Kernel filter",
     [](model::texture_processors::GlTextureProcessorFactory& factory) {
         return std::make_unique<texture_processors::KernelTextureProcessorView>(factory);
     }},
    {"Edge detector filter", [](model::texture_processors::GlTextureProcessorFactory& factory) {
         return std::make_unique<texture_processors::EdgeDetectorTextureProcessorView>(factory);
     }}};

TextureProcessorsListView::TextureProcessorsListView(Model& model, std::string window_name)
    : model_{model}, window_name_(std::move(window_name)) {}

void TextureProcessorsListView::RenderIndexed() {
    ImGuiFocusedFlags window_flags{};
    if (ImGui::Begin(window_name_.c_str(), nullptr, window_flags)) {
        std::string header = "Texture processors";
        const float font_size = ImGui::GetFontSize() * header.size() / 2;
        ImGui::SameLine(ImGui::GetWindowSize().x / 2 - (font_size / 2));
        ImGui::Text("%s", header.c_str());

        show_factory_popup_ |= ImGui::Button("Create");

        for (auto& image_processor_view : image_processor_views_) {
            image_processor_view->Render();
        }

        ImGui::End();
    }

    ProcessImageProcessors();
    RenderFactoryPopup();
}

void TextureProcessorsListView::ProcessImageProcessors() {
    bool changed = false;

    for (auto it = std::begin(image_processor_views_); it != std::end(image_processor_views_);) {
        bool changed_view = true;
        auto& image_processor_view = *it;
        if (image_processor_view->WantMoveUp() && it != std::begin(image_processor_views_)) {
            std::swap(*it, *std::next(it, -1));
        } else if (image_processor_view->WantMoveDown() &&
                   std::next(it) != std::end(image_processor_views_)) {
            std::swap(*it, *std::next(it));
            ++it;
        } else if (image_processor_view->WantClose()) {
            it = image_processor_views_.erase(it);
        } else {
            changed_view &= image_processor_view->Changed();
            ++it;
        }
        changed |= changed_view;
    }

    if (changed) {
        UpdateTextureProcessors();
    }
}
void TextureProcessorsListView::UpdateTextureProcessors() const {
    std::vector<std::unique_ptr<model::texture_processors::GlTextureProcessor>> texture_processors;

    for (const auto& image_processor_view : image_processor_views_) {
        texture_processors.emplace_back(image_processor_view->CreateTextureProcessor());
    }

    model_.SetImageProcessors(std::begin(texture_processors), std::end(texture_processors));
}

void TextureProcessorsListView::RenderFactoryPopup() {
    const std::string popup_window_name = "Create texture processor";

    if (show_factory_popup_) ImGui::OpenPopup(popup_window_name.c_str());
    if (ImGui::BeginPopupModal(popup_window_name.c_str(), &show_factory_popup_)) {
        const auto& chosen_factory = kTextureProcessorFactoryViews[factory_index_];
        if (ImGui::BeginCombo("Texture processor", chosen_factory.title.c_str())) {
            for (unsigned int i = 0; i < kTextureProcessorFactoryViews.size(); i++) {
                const auto& factory = kTextureProcessorFactoryViews[i];
                bool is_selected = i == factory_index_;
                if (ImGui::Selectable(factory.title.c_str(), &is_selected)) factory_index_ = i;
                if (is_selected) ImGui::SetItemDefaultFocus();
            }

            ImGui::EndCombo();
        }

        if (ImGui::Button("Ok")) {
            Append(chosen_factory.factory_method(model_.GetTextureProcessorFactory()));
            show_factory_popup_ = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel")) show_factory_popup_ = false;

        ImGui::EndPopup();
    }
}

void TextureProcessorsListView::Append(std::unique_ptr<ItemView> image_processor_view) {
    image_processor_views_.push_back(std::move(image_processor_view));
    UpdateTextureProcessors();
}

}  // namespace image_processor::view
