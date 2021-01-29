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
    //float vtx[6] = {left, top, 0.0f, right, top, 0.0f};
    alfons::draw::Line line;
    line.strokeWidth = 10;
    line.setVertexes(left, top, right, top);
    line.setColorF(.8f, .8f, 0.0f, 1.0f);
    lineRender.addLine(line);

    //lt, lb
    //float vtx2[6] = {left, top, 0.0f, left, bottom, 0.0f};
    line.setVertexes(left, top, left, bottom);
    line.setColorF(.8f, .8f, 0.0f, 1.0f);
    lineRender.addLine(line);

    //rt, rb
    //float vtx3[6] = {right, top, 0.0f, right, bottom, 0.0f};
    line.setVertexes(right, top, right, bottom);
    line.setColorF(.8f, .8f, 0.0f, 1.0f);
    lineRender.addLine(line);

    //lb, rb
    //float vtx4[6] = {left, bottom, 0.0f, right, bottom, 0.0f};
    line.setVertexes(left, bottom, right, bottom);
    line.setColorF(.8f, .8f, 0.0f, 1.0f);
    lineRender.addLine(line);

    alfons::draw::Rect rect;
    rect.strokeWidth = 30;//TODO glLineWidth only can used once? move to rect
    rect.setColorF(1.0f, 0.0f, 0.0f, 1.0f);
    rect.setRect(200, 500, 400, 700);
    lineRender.addRect(rect, false);

    rect.setRect(400, 0, 600, 200);
    lineRender.addRect(rect, true);
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

