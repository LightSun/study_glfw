//
// Created by Administrator on 2021/1/23 0023.
//

#ifndef STUDYGLEWAPP_SIMPLEFONTRENDER_H
#define STUDYGLEWAPP_SIMPLEFONTRENDER_H

#include "JNIRender.h"

class SimpleFontRender: public JNIRender{

public:
    virtual void destroy();
    virtual void init(const char* fontDir);
    virtual void resize(long ptr, int width, int height);
    virtual void draw();
};

#endif //STUDYGLEWAPP_SIMPLEFONTRENDER_H
