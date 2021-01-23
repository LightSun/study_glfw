//
// Created by Administrator on 2021/1/23 0023.
//

#include <render/gl.h>
#include "AlfonsFontRender.h"

extern "C" void onSetup(const char *fontDir);
extern "C" void onDraw(int width, int height);

void AlfonsFontRender::init(const char *fontDir) {
    onSetup(fontDir);
}

void AlfonsFontRender::draw() {
    glViewport(0, 0, width, height);
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT |
            GL_STENCIL_BUFFER_BIT);
    onDraw(width, height);
}

void AlfonsFontRender::destroy() {

}