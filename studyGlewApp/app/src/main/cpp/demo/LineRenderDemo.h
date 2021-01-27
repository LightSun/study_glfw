//
// Created by Administrator on 2021/1/27 0027.
//

#ifndef STUDYGLEWAPP_LINERENDERDEMO_H
#define STUDYGLEWAPP_LINERENDERDEMO_H

#include <alfons/src/alfons/LineRender.h>
#include "../JNIRender.h"

class LineRenderDemo: public JNIRender{
public:
    virtual void destroy();
    virtual void init(const char* fontDir);
    virtual void draw();
    virtual void doTest();

private:
    alfons::LineRender lineRender;
};

#endif //STUDYGLEWAPP_LINERENDERDEMO_H
