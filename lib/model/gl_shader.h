#ifndef IMAGEPROCESSOR_GL_SHADER_H
#define IMAGEPROCESSOR_GL_SHADER_H

#include <glad/gl.h>

#include <filesystem>

namespace image_processor::model {

class GlShader {
  public:
    using Path = std::filesystem::path;

    GlShader(GLenum type, const Path& path);
    GlShader(GLenum type, const std::string& source);
    GlShader(GlShader&& other) noexcept;
    GlShader& operator=(GlShader&& other);
    ~GlShader();

    auto GetID() const -> GLuint { return id_; };
    static auto LoadShader(const Path& path) -> std::string;

  private:
    GlShader(const GlShader& other) = default;
    GlShader& operator=(const GlShader& other) = default;
    static auto CreateShader(GLenum type, const std::string& source) -> GLuint;

    GLuint id_;
};

}  // namespace image_processor::model

#endif  // IMAGEPROCESSOR_GL_SHADER_H
