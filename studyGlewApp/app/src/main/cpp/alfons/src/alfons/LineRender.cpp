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
    void LineRender::addLine(alfons::draw::Line &line) {
        if(line.strokeWidth > 1){
            //for glLineWidth can only effect once in one draw. so we used rect to draw stroke line.
            alfons::draw::Rect rect;
            rect.color = line.color;
            line.strokeRect(rect);
            addRect(rect, true);
        } else{
            lines.insert(lines.begin() + lines.size(), line);
        }
    }
    void LineRender::addRect(alfons::draw::Rect &rect, bool fill) {
        if(fill){
            fillRects.insert(fillRects.begin() + fillRects.size(), rect);
        } else{
            float left = rect.left();
            float top = rect.top();
            float right = rect.right();
            float bottom = rect.bottom() ;

            alfons::draw::Line line;
            line.strokeWidth = rect.strokeWidth;
            line.color = rect.color;
            //lt, rt
            float vtx[6] = {left, top, 0.0f, right, top, 0.0f};
            line.setVertexes(vtx);
            addLine(line);

            //rt, rb
            float vtx3[6] = {right, top, 0.0f, right, bottom, 0.0f};
            line.setVertexes(vtx3);
            addLine(line);

            //lb, rb
            float vtx4[6] = {left, bottom, 0.0f, right, bottom, 0.0f};
            line.setVertexes(vtx4);
            addLine(line);

            //lt, lb
            float vtx2[6] = {left, top, 0.0f, left, bottom, 0.0f};
            line.setVertexes(vtx2);
            addLine(line);
        }
    }

    void LineRender::destroy() {
        shader->destroy();
    }
    void LineRender::draw() {
        glm::mat4 projectionMatrix = glm::ortho(0.0, double(width),
                double(height), 0.0,
                       -1.0, 1.0);

        shader->use();
        glEnableVertexAttribArray(PositionHandle);

        float color[4];
        //draw lines
        for (int i = 0; i < lines.size(); ++i) {
            auto& line = lines[i];
            line.getColor(color);

            glLineWidth(line.strokeWidth);

            // vertex .absolute cors
            glVertexAttribPointer(PositionHandle, COORDS_PER_VERTEX, GL_FLOAT, GL_FALSE,
                    VertexStride, &line.vertexes[0]);

            // color
            glUniform4fv(ColorHandle, 1, &color[0]);

            //mvp
            glUniformMatrix4fv(MVPHandle, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
            GLUT::glCheckError("glUniformMatrix4fv: MVPHandle");

            // Draw
            glDrawArrays(GL_LINES, 0, VertexCount);
        }
        //draw fill rects
        if(fillRects.size() > 0){
            u_short drawOrder[6] = { 0, 1, 2, 0, 2, 3 };
            for (int i = 0; i < fillRects.size(); ++i) {
                auto& rect = fillRects[i];
                rect.getColor(color);

                //每组： COORDS_PER_VERTEX
                glVertexAttribPointer(PositionHandle, COORDS_PER_VERTEX,
                                      GL_FLOAT, GL_FALSE, VertexStride, &rect.vertexes[0]);
                glUniform4fv(ColorHandle, 1, &color[0]);
                glUniformMatrix4fv(MVPHandle, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

                //draw rect
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, &drawOrder[0]);
            }
        }
        glDisableVertexAttribArray(PositionHandle);
    }
}