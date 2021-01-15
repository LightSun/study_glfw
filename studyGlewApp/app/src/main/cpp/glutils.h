#pragma once

//#include "import_gl.h"

#if defined(ANDROID)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
//#include <GLES/gl.h>
//#include <GLES/glext.h>
#endif
#include <vector>
#include "Matrix4f.h"
#include "log.h"

namespace gl {
    GLuint program;
    GLuint vertex;
    GLuint fragment;

    GLint positionLoc;
    GLint uvLoc;
    GLint vMatrix;
    bool exist;

    h7::Matrix4f mvpMat;
    GLint uTex;
    int textureType = 0;

    struct Vertex {
        float x, y;
        float s, t;

        Vertex() {}
        Vertex(float _x, float _y, float _s, float _t) : x(_x), y(_y), s(_s), t(_t) {}
    };

    typedef struct {
        unsigned short* indices;
        unsigned char* textureData;
        unsigned int textureId;
        Vertex* vertices;
        unsigned int nbIndices;
        unsigned int nbVertices;
        GLuint vertexBuffer;
        GLuint indexBuffer;
    } Mesh;
    /*I/AdrenoGLES: ERROR: 0:5: 'gl_ProjectionMatrix' : undeclared identifier
    ERROR: 0:5: 'gl_ModelViewMatrix' : undeclared identifier
    ERROR: 2 compilation errors.  No code generated.
     I/AdrenoGLES: ERROR: 0:5: 'gl_ProjectionMatrix' : undeclared identifier
    ERROR: 0:5: 'gl_ModelViewMatrix' : undeclared identifier*/
    static const GLchar* vertexSrc =
        "attribute vec4 a_position;\n"
        "uniform mat4 vMatrix;\n"
        "attribute vec2 a_uv;\n"
        "varying vec2 f_uv;\n"
        "void main() {\n"
        "gl_Position = vMatrix * a_position;\n"
        "f_uv = a_uv;\n"
        "}\n";

    static const GLchar* fragmentSrc =
        "uniform sampler2D u_tex;\n"
        "varying vec2 f_uv;\n"
        "void main() {\n"
        "    gl_FragColor = texture2D(u_tex, f_uv);\n"
        "}\n";
    static inline void checkGLError(const char* op) {
        int error;
        while ((error = glGetError()) != GL_NO_ERROR) {
            LOGE("%s: glError %d", op , error);
        }
    }
    void createShaderProgram() {
        LOGD("----------- start createShaderProgram -------------");
        program = glCreateProgram();
        checkGLError("glCreateProgram");
        vertex = glCreateShader(GL_VERTEX_SHADER);
        checkGLError("glCreateShader vertex");
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        checkGLError("glCreateShader fragment");

        glShaderSource(fragment, 1, &fragmentSrc, NULL);
        checkGLError("glShaderSource fragment");
        glCompileShader(fragment);
        checkGLError("glCompileShader fragment");
        glAttachShader(program, fragment);
        checkGLError("glAttachShader fragment");

        glShaderSource(vertex, 1, &vertexSrc, NULL);
        checkGLError("glShaderSource vertex");
        glCompileShader(vertex);
        checkGLError("glCompileShader vertex");
        glAttachShader(program, vertex);
        checkGLError("glAttachShader vertex");

        glLinkProgram(program);
        checkGLError("glLinkProgram");

        uTex = glGetUniformLocation(program, "u_tex"); //must use glUniform1i on draw
        checkGLError("glGetUniformLocation u_tex");

        positionLoc = glGetAttribLocation(program, "a_position");
        checkGLError("glGetAttribLocation: a_position ");
        uvLoc =	glGetAttribLocation(program, "a_uv");
        checkGLError("glGetAttribLocation: a_uv ");

        vMatrix = glGetUniformLocation(program, "vMatrix");
        checkGLError("glGetUniformLocation: vMatrix ");
    }

    void render(const std::vector<Mesh*> meshes) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(program);

        //glUniform1i: 对这几个纹理采样器变量进行设置 . ps: https://blog.csdn.net/mumuzi_1/article/details/62047112
        glActiveTexture(GL_TEXTURE0 + textureType);
        glUniform1i(uTex, textureType);

        for(auto mesh: meshes) {
            glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
            glBindTexture(GL_TEXTURE_2D, mesh->textureId);

            glEnableVertexAttribArray(positionLoc);
            glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
            glEnableVertexAttribArray(uvLoc);
            glVertexAttribPointer(uvLoc, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const GLvoid*)(2 * sizeof(float)));

            glDrawElements(GL_TRIANGLES, mesh->nbIndices, GL_UNSIGNED_SHORT, 0);
        }

        glUseProgram(0);
    }

    void resize(int w, int h) {
        mvpMat.loadOrthoWindow(w, h);
    }

    void finish() {
        glDeleteShader(fragment);
        glDeleteShader(vertex);
        glDeleteProgram(program);
    }

    //不能同时连接gles1 和gles2 ??
    void initGL(int width, int height) {
        glClearColor(1, 1, 1, 1);
        glViewport(0, 0, width, height);

       // createShaderProgram();

       // GLES20.glUniformMatrix4fv(mMatrix, 1, false, mMVPMatrix, 0);
        glUniformMatrix4fv(vMatrix, 1, static_cast<GLboolean>(false), mvpMat.getValues());

       /* glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //glOrtho(0, width, 0, height, -1, 1);
        glOrthox(0, width, 0, height, -1, 1);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();*/

        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void loop(const std::vector<Mesh*> meshes) {
       /* while(true) {
            render(meshes);
        }*/
    }

    void uploadMeshes(const std::vector<Mesh*> meshes) {
        for(auto mesh: meshes) {
            std::vector<float> data;

            for(int i = 0; i < mesh->nbVertices; i++) {
                data.push_back(mesh->vertices[i].x);
                data.push_back(mesh->vertices[i].y);
                data.push_back(mesh->vertices[i].s);
                data.push_back(mesh->vertices[i].t);
            }

            glBindTexture(GL_TEXTURE_2D, mesh->textureId);

            glGenBuffers(1, &mesh->vertexBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
            glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

            glGenBuffers(1, &mesh->indexBuffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->nbIndices * sizeof(unsigned short), mesh->indices, GL_STATIC_DRAW);
        }
    }

    void deleteMeshes(std::vector<Mesh*> meshes) {
        for(auto mesh: meshes) {
            delete[] mesh->textureData;

            glDeleteTextures(1, &mesh->textureId);
            glDeleteBuffers(1, &mesh->indexBuffer);
            glDeleteBuffers(1, &mesh->vertexBuffer);

            delete[] mesh->vertices;
            delete[] mesh->indices;
            delete mesh;
        }
        meshes.clear();
    }

    unsigned int getTextureId(int width, int height) {
        GLuint textureId;

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        return textureId;
    }

    void uploadTextureData(unsigned int textureId, int width, int height, unsigned char* data) {
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, data);
    }
}
