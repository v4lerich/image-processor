#ifndef IMAGEPROCESSOR_APPLICATION_CONFIG_H
#define IMAGEPROCESSOR_APPLICATION_CONFIG_H

namespace image_processor::config {

enum class ApplicationTheme {
    kClassic,
    kLight,
    kDark
};

struct OpenGlVersion {
    int major;
    int minor;
};

constexpr auto kWindowWidth = 1280;
constexpr auto kWindowHeight = 720;

constexpr auto kVsyncValue = -1; // Adaptive VSYNC
constexpr auto kImGuiTheme = ApplicationTheme::kClassic;

constexpr auto kOpenGlVersion = OpenGlVersion { .major = 4, .minor = 2 };
constexpr auto kGlslVersion = "#version 420";

}

#endif  // IMAGEPROCESSOR_APPLICATION_CONFIG_H
