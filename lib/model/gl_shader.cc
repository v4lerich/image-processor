#include "gl_shader.h"

#include <exception>
#include <fstream>

namespace image_processor::model {

GlShader::GlShader(GLenum type, const Path& path) {
    std::string source = LoadShader(path);
    id_ = CreateShader(type, source);
}

GlShader::GlShader(GLenum type, const std::string& source) { id_ = CreateShader(type, source); }

GlShader::GlShader(GlShader&& other) noexcept { *this = std::move(other); }

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

auto GlShader::CreateShader(GLenum type, const std::string& source) -> GLuint {
    auto source_c_str = source.c_str();
    GLuint shader_id = glCreateShader(type);
    glShaderSource(shader_id, 1, &source_c_str, nullptr);

    glCompileShader(shader_id);

    GLint compilation_status;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compilation_status);
    if (compilation_status != GL_TRUE) {
        int info_log_length;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

        std::string info_log;
        info_log.resize(info_log_length);
        glGetShaderInfoLog(shader_id, info_log_length, nullptr, info_log.data());

        glDeleteShader(shader_id);
        throw std::runtime_error("Shader compilation error: " + info_log);
    }
    return shader_id;
}

auto GlShader::LoadShader(const GlShader::Path& path) -> std::string {
    std::ifstream ifstream{path, std::ios::in};
    if (ifstream.fail()) {
        throw std::runtime_error{"Shader is not found in: " + path.string()};
    }

    std::string source{std::istreambuf_iterator<char>{ifstream}, std::istreambuf_iterator<char>{}};
    return source;
}

}  // namespace image_processor::model
