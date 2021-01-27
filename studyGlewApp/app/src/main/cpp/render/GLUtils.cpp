//
// Created by Administrator on 2021/1/27 0027.
//

#include "GLUtils.h"
#include <cstdint>
#include <cstdlib>

static void printShaderInfoLog(GLuint shader) {
    GLint length = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
    if (length > 1) {
        char* log = (char*) malloc(sizeof(char) * length);
        glGetShaderInfoLog(shader, length, NULL, log);
        printf("Log: %s\n", log);
        free(log);
    }
}

static GLuint compileShader(const GLchar* src, GLenum type) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (!status) {
        printShaderInfoLog(shader);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

namespace GLUT{
    GLuint linkShaderProgram(const GLchar* vertexSrc, const GLchar* fragmentSrc) {
        GLuint program = glCreateProgram();
        GLuint vertex = compileShader(vertexSrc, GL_VERTEX_SHADER);
        GLuint fragment = compileShader(fragmentSrc, GL_FRAGMENT_SHADER);
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);
        glLinkProgram(program);
        GLint linkStatus;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

        if (!linkStatus) {
            glCheckError("linkShaderProgram");
            printShaderInfoLog(program);
            glDeleteProgram(program);
            return 0;
        }
        return program;
    }
    void glCheckError(const char* str) {
        GLenum err;
        err = glGetError();
        if (err != GL_NO_ERROR) {
            printf("Error %08x %d after %s\n", err, err, str);
            return;
        }
    }
}
