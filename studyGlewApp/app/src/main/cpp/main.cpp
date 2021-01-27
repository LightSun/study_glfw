#include <iostream>
#include <ctime>
#include <demo/AlfonsFontRender.h>
#include <demo/SimpleFontRender.h>
#include <demo/LineRenderDemo.h>

#include "log.h"
#include "JNIRender.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_heaven7_android_glew_app_JNIApi_nInit(JNIEnv*env,
                                               jclass thiz, jlong  ptr, jstring
                                               font_dir){
    JNIRender* _render = reinterpret_cast<JNIRender *>(ptr);
    if(font_dir == nullptr){
        _render->init(nullptr);
    } else{
        auto fontDir = env->GetStringUTFChars(font_dir, NULL);
        LOGD("fontDir = %s", fontDir);
        _render->init(fontDir);
        env->ReleaseStringUTFChars(font_dir, fontDir);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_heaven7_android_glew_app_JNIApi_nResize(JNIEnv
                                                 *env,
                                                 jclass cls, jlong ptr, jint
                                                 width,
                                                 jint height
){
    JNIRender* _render = reinterpret_cast<JNIRender *>(ptr);
    _render->resize(width , height);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_heaven7_android_glew_app_JNIApi_nDraw(JNIEnv
                                               *env,
                                               jclass cls, jlong ptr
){
    JNIRender* _render = reinterpret_cast<JNIRender *>(ptr);
    _render->draw();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_heaven7_android_glew_app_JNIApi_nDestroy(JNIEnv
                                                  *env,
                                                  jclass cls, jlong ptr
){
    JNIRender* _render = reinterpret_cast<JNIRender *>(ptr);
    _render->destroy();
    delete _render;
}extern "C"
JNIEXPORT jlong JNICALL
Java_com_heaven7_android_glew_app_JNIApi_nCreate(JNIEnv *env, jclass cls, jint type) {
#define RENDER_TYPE_ALFONS 1
#define RENDER_TYPE_LINE 2
    JNIRender* ptr;
    switch (type){
        case RENDER_TYPE_ALFONS:
            ptr = new AlfonsFontRender();
            break;

        case RENDER_TYPE_LINE:
            ptr = new LineRenderDemo();
            break;
        default:
            return 0;
    }
    ptr->env = env;
    return reinterpret_cast<jlong>(ptr);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_heaven7_android_glew_app_JNIApi_nAfterInit(JNIEnv *env, jclass clazz, jlong ptr) {
    JNIRender* _render = reinterpret_cast<JNIRender *>(ptr);
    _render->doTest();
}