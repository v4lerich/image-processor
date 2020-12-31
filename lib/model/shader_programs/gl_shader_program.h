#ifndef IMAGEPROCESSOR_GL_SHADER_PROGRAM_H
#define IMAGEPROCESSOR_GL_SHADER_PROGRAM_H

#include <gl_shader.h>
#include <glad/gl.h>

#include <filesystem>
#include <initializer_list>

namespace image_processor::model::shader_programs {

template <typename T>
concept GlShaderIterator = std::is_same_v<GlShader, typename std::iterator_traits<T>::value_type>;

class GlShaderProgram {
  public:
    template <GlShaderIterator Iterator>
    GlShaderProgram(Iterator first, Iterator last) {
        program_id_ = std::shared_ptr<GLuint>(new GLuint(glCreateProgram()), DeleteShaderProgram);
        for (Iterator it = first; it != last; ++it) {
            glAttachShader(*program_id_, it->GetID());
        }
        glLinkProgram(*program_id_);

        GLint link_status;
        glGetProgramiv(*program_id_, GL_LINK_STATUS, &link_status);

        if (link_status != GL_TRUE) {
            int info_log_length;
            glGetProgramiv(*program_id_, GL_INFO_LOG_LENGTH, &info_log_length);

            std::string info_log;
            info_log.resize(info_log_length);
            glGetProgramInfoLog(*program_id_, info_log_length, nullptr, info_log.data());

            glDeleteProgram(*program_id_);
            throw std::runtime_error("Program link error: " + info_log);
        }
    }
    GlShaderProgram(std::initializer_list<GlShader> shaders);

    auto GetID() const -> GLuint { return *program_id_; }

  private:
    static void DeleteShaderProgram(GLuint* program_id);

    std::shared_ptr<GLuint> program_id_;
};

}  // namespace image_processor::model::shader_programs

#endif  // IMAGEPROCESSOR_GL_SHADER_PROGRAM_H
