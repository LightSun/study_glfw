//
// Created by Administrator on 2021/1/27 0027.
//

#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#include "LineRender.h"
#include "GLUtils.h"

namespace alfons{
    void LineRender::init(){
        shader = new GLUT::Shader(VertexShaderCode, FragmentShaderCode);
        // get handle to vertex shader's vPosition member
        PositionHandle = glGetAttribLocation(shader->program, "vPosition");
        GLUT::glCheckError("glGetUniformLocation: vPosition");
        // get handle to fragment shader's vColor member
        ColorHandle = glGetUniformLocation(shader->program, "vColor");
        GLUT::glCheckError("glGetUniformLocation: vColor");

        MVPHandle = glGetUniformLocation(shader->program, "uMVPMatrix");
        GLUT::glCheckError("glGetUniformLocation: uMVPMatrix");
    }
    void LineRender::setViewPort(int w, int h) {
        width = w;
        height = h;
    }
    void LineRender::clearLines() {
        lines.clear();
    }
    void LineRender::addLine(alfons::Line &line) {
        lines.insert(lines.begin() + lines.size(), line);
    }

    void LineRender::destroy() {
        shader->destroy();
    }
    void LineRender::draw() {
        glm::mat4 projectionMatrix = glm::ortho(0.0,
                                      double(width),
                                      double(height),
                                      0.0, -1.0, 1.0);

        shader->use();
        float color[4];
        for (int i = 0; i < lines.size(); ++i) {
            auto& line = lines[i];
            line.getColor(color);
            glLineWidth(line.lineWidth);

            glEnableVertexAttribArray(PositionHandle);
            // vertex
            glVertexAttribPointer(PositionHandle, COORDS_PER_VERTEX, GL_FLOAT, GL_FALSE,
                    VertexStride, &line.vertexes[0]);

            // color
            glUniform4fv(ColorHandle, 4, &color[0]);

            //mvp
            glUniformMatrix4fv(MVPHandle, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
            GLUT::glCheckError("glUniformMatrix4fv: MVPHandle");

            // Draw
            glDrawArrays(GL_LINES, 0, VertexCount);

            glDisableVertexAttribArray(PositionHandle);
        }
    }
}