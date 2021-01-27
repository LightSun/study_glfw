//
// Created by Administrator on 2021/1/27 0027.
//

#ifndef STUDYGLEWAPP_GLUTILS_H
#define STUDYGLEWAPP_GLUTILS_H

#include <string>
#include <glm/glm.hpp>
#include "gl.h"

namespace GLUT{

    GLuint linkShaderProgram(const GLchar *vertexSrc, const GLchar *fragmentSrc);
    void glCheckError(const char *str);

    class Shader {
    public:
        unsigned int program;

        // ------------------------------------------------------------------------
        Shader(const char *vertexStr, const char *fragmentStr) {
            program = linkShaderProgram(vertexStr, fragmentStr);
        }

        ~Shader() {
        }

        void destroy() {
            glDeleteProgram(program);
        }

        // activate the shader
        // ------------------------------------------------------------------------
        void use() {
            glUseProgram(program);
        }

        // utility uniform functions
        // ------------------------------------------------------------------------
        void setBool(const std::string &name, bool value) const {
            glUniform1i(glGetUniformLocation(program, name.c_str()), (int) value);
        }

        // ------------------------------------------------------------------------
        void setInt(const std::string &name, int value) const {
            glUniform1i(glGetUniformLocation(program, name.c_str()), value);
        }

        // ------------------------------------------------------------------------
        void setFloat(const std::string &name, float value) const {
            glUniform1f(glGetUniformLocation(program, name.c_str()), value);
        }

        // ------------------------------------------------------------------------
        void setVec2(const std::string &name, const glm::vec2 &value) const {
            glUniform2fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
        }

        void setVec2(const std::string &name, float x, float y) const {
            glUniform2f(glGetUniformLocation(program, name.c_str()), x, y);
        }

        // ------------------------------------------------------------------------
        void setVec3(const std::string &name, const glm::vec3 &value) const {
            glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
        }

        void setVec3(const std::string &name, float x, float y, float z) const {
            glUniform3f(glGetUniformLocation(program, name.c_str()), x, y, z);
        }

        // ------------------------------------------------------------------------
        void setVec4(const std::string &name, const glm::vec4 &value) const {
            glUniform4fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
        }

        void setVec4(const std::string &name, float value[4]) const {
            glUniform4fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
        }

        void setVec4(const std::string &name, float x, float y, float z, float w) {
            glUniform4f(glGetUniformLocation(program, name.c_str()), x, y, z, w);
        }

        // ------------------------------------------------------------------------
        void setMat2(const std::string &name, const glm::mat2 &mat) const {
            glUniformMatrix2fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

        // ------------------------------------------------------------------------
        void setMat3(const std::string &name, const glm::mat3 &mat) const {
            glUniformMatrix3fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

        // ------------------------------------------------------------------------
        void setMat4(const std::string &name, const glm::mat4 &mat) const {
            glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

    };
}

#endif //STUDYGLEWAPP_GLUTILS_H
