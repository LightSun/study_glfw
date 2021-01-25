package com.heaven7.android.glew.app;

import android.opengl.GLSurfaceView;

public abstract class IGLRender implements GLSurfaceView.Renderer {

    public int getRenderMode(){
        return GLSurfaceView.RENDERMODE_CONTINUOUSLY;
    }

    public int getEGLVersion(){
        return 3;
    }

    public abstract void setUp(Runnable next);
}
