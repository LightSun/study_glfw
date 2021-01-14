//
// Created by Administrator on 2021/1/14 0014.
//

#ifndef STUDYGLEWAPP_JNIAPI_H
#define STUDYGLEWAPP_JNIAPI_H

#include <jni.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_heaven7_android_glew_app_JNIApi_nInit(JNIEnv
                                               *env,
                                               jobject thiz, jstring
                                               font_dir,
                                               jint width, jint
                                               height);

extern "C"
JNIEXPORT void JNICALL
Java_com_heaven7_android_glew_app_JNIApi_nResize(JNIEnv
                                                 *env,
                                                 jobject thiz, jint
                                                 width,
                                                 jint height
);

extern "C"
JNIEXPORT void JNICALL
Java_com_heaven7_android_glew_app_JNIApi_nDraw(JNIEnv
                                               *env,
                                               jobject thiz
);

extern "C"
JNIEXPORT void JNICALL
Java_com_heaven7_android_glew_app_JNIApi_nDestroy(JNIEnv
                                               *env,
                                               jobject thiz
);

#endif //STUDYGLEWAPP_JNIAPI_H
