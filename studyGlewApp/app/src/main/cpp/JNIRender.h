//
// Created by Administrator on 2021/1/23 0023.
//

#ifndef STUDYGLEWAPP_JNIRENDER_H
#define STUDYGLEWAPP_JNIRENDER_H

#include <jni.h>

class JNIRender{

public:
    JNIEnv* env;
    int width;
    int height;
    void attachEnv(JNIEnv* e){
        this->env = e;
    }
    virtual void destroy(){}
    virtual void init(const char* fontDir){}
    virtual void resize(int w, int h){
        width = w;
        height = h;
    }
    virtual void draw(){}

    virtual void doTest() {
    }
};

char *merge(const char *s1, const char *s2);

#define MERGE_STR2(chs, chs2, x)\
{ \
auto ch = merge(chs, chs2);\
x;\
free(ch);\
}

#endif //STUDYGLEWAPP_JNIRENDER_H
