#ifndef IMAGEPROCESSOR_APPLICATION_CONFIG_H
#define IMAGEPROCESSOR_APPLICATION_CONFIG_H

#include <IconsForkAwesome.h>

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

const std::string kResourcePath = "../res/";
const std::string kRubikFontPath = kResourcePath + "RubikFont/Rubik-Medium.ttf";
const std::string kForkAwesomeFontPath = kResourcePath + "ForkAwesomeFont/" + FONT_ICON_FILE_NAME_FK;

}

#endif  // IMAGEPROCESSOR_APPLICATION_CONFIG_H
