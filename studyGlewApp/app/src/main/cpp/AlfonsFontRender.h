//
// Created by Administrator on 2021/1/23 0023.
//

#ifndef STUDYGLEWAPP_ALFONSFONTRENDER_H
#define STUDYGLEWAPP_ALFONSFONTRENDER_H

#include "JNIRender.h"

class AlfonsFontRender: public JNIRender{

public:
    virtual void destroy();
    virtual void init(const char* fontDir);
    virtual void draw();
};

#endif //STUDYGLEWAPP_ALFONSFONTRENDER_H
