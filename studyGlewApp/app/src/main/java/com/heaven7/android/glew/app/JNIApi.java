package com.heaven7.android.glew.app;

public final class JNIApi {

    static {
        System.loadLibrary("studyGlfw");
    }

    public void init(String fontDir){
       nInit(fontDir, 0, 0);
    }

    public void resize(int width, int height){
        nResize(width, height);
    }
    public void draw(){
        nDraw();
    }
    public void destroy(){
        nDestroy();
    }
    private native void nInit(String fontDir, int width, int height);
    private native void nResize(int width, int height);
    private native void nDraw();
    private native void nDestroy();
}
