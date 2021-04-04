//
// Created by Administrator on 2021/1/23 0023.
//

#include <render/gl.h>
#include "AlfonsFontRender.h"

//opencv: 显示中文
//https://blog.csdn.net/qq_35705332/article/details/90603371?utm_medium=distribute.pc_relevant.none-task-blog-baidujs_title-4&spm=1001.2101.3001.4242
extern "C" void onSetup(const char *fontDir);
extern "C" void onDraw(int width, int height);
extern "C" void doTest0(int width, int height);

void AlfonsFontRender::init(const char *fontDir) {
    onSetup(fontDir);
}

void AlfonsFontRender::draw() {
    glViewport(0, 0, width, height);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT |
            GL_STENCIL_BUFFER_BIT);
    onDraw(width, height);
}

void AlfonsFontRender::destroy() {

}
void AlfonsFontRender::doTest() {
    doTest0(width, height);
}