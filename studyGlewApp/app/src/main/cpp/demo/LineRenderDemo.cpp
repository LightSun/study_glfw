//
// Created by Administrator on 2021/1/27 0027.
//

#include "LineRenderDemo.h"
#include "alfons/LineRender.h"

void LineRenderDemo::init(const char *fontDir) {
    lineRender.init();
}

void LineRenderDemo::doTest() {
    lineRender.setViewPort(width, height);
    lineRender.clearLines();

    //l, t, r, b
    float left = 200;
    float top = 200;
    float right = 400;
    float bottom = 400;

    //lt, rt
    float vtx[6] = {left, top, 0.0f, right, top, 0.0f};
    alfons::Line line;
    line.lineWidth = 10;
    line.setVertexes(vtx);
    line.setColorF(.8f, .8f, 0.0f, 1.0f);
    lineRender.addLine(line);

    //lt, lb
    float vtx2[6] = {left, top, 0.0f, left, bottom, 0.0f};
    line.setVertexes(vtx2);
    line.setColorF(.8f, .8f, 0.0f, 1.0f);
    lineRender.addLine(line);

    //rt, rb
    float vtx3[6] = {right, top, 0.0f, right, bottom, 0.0f};
    line.setVertexes(vtx3);
    line.setColorF(.8f, .8f, 0.0f, 1.0f);
    lineRender.addLine(line);

    //lb, rb
    float vtx4[6] = {left, bottom, 0.0f, right, bottom, 0.0f};
    line.setVertexes(vtx4);
    line.setColorF(.8f, .8f, 0.0f, 1.0f);
    lineRender.addLine(line);
}

void LineRenderDemo::draw() {
    glViewport(0, 0, width, height);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT |
            GL_STENCIL_BUFFER_BIT);

    lineRender.draw();
}

void LineRenderDemo::destroy() {
    lineRender.destroy();
}

