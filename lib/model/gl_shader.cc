#include "gl_shader.h"

#include <exception>
#include <fstream>

namespace image_processor::model {

GlShader::GlShader(GLenum type, const Path& path) {
    id_ = glCreateShader(type);

    std::ifstream ifstream{path, std::ios::in};
    if (ifstream.fail()) {
        throw std::runtime_error{"Shader is not found in: " + path.string()};
    }

    std::string source{std::istreambuf_iterator<char>{ifstream}, std::istreambuf_iterator<char>{}};
    auto source_c_str = source.c_str();
    glShaderSource(id_, 1, &source_c_str, nullptr);

    glCompileShader(id_);

    GLint compilation_status;
    glGetShaderiv(id_, GL_COMPILE_STATUS, &compilation_status);
    if (compilation_status != GL_TRUE) {
        int info_log_length;
        glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &info_log_length);

        std::string info_log;
        info_log.resize(info_log_length);
        glGetShaderInfoLog(id_, info_log_length, nullptr, info_log.data());

        glDeleteShader(id_);
        throw std::runtime_error("Shader compilation error: " + info_log);
    }
}

GlShader::GlShader(GlShader&& other) noexcept {
    *this = std::move(other);
}

GlShader& GlShader::operator=(GlShader&& other) {
    id_ = other.id_;
    other.id_ = 0;
    return *this;
}

GlShader::~GlShader() {
    if (id_ != 0) {
        glDeleteShader(id_);
    }
}

}  // namespace image_processor::model
