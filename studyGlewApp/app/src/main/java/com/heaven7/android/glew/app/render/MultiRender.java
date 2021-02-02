package com.heaven7.android.glew.app.render;

import android.app.Activity;
import android.opengl.GLSurfaceView;

import com.heaven7.android.glew.app.IGLRender;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

//TODO test font render with LineRender failed
public class MultiRender extends IGLRender {

    private final FontRender fontRender;
    private final LineRenderDemo lineRenderDemo;

    public MultiRender(Activity context) {
        super(context);
        fontRender = new FontRender(context);
        lineRenderDemo = new LineRenderDemo(context);
    }

    @Override
    public int getRenderMode() {
        return GLSurfaceView.RENDERMODE_CONTINUOUSLY;
    }

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        fontRender.onSurfaceCreated(gl10, eglConfig);
        lineRenderDemo.onSurfaceCreated(gl10, eglConfig);
    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int i, int i1) {
        fontRender.onSurfaceChanged(gl10, i, i1);
        lineRenderDemo.onSurfaceChanged(gl10, i, i1);
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        fontRender.onDrawFrame(gl10);
        lineRenderDemo.onDrawFrame(gl10);
    }

    @Override
    public void setUp(Runnable next) {
        fontRender.setUp(new Runnable() {
            @Override
            public void run() {
                lineRenderDemo.setUp(next);
            }
        });
    }

    @Override
    public void onDestroy() {
        fontRender.onDestroy();
        lineRenderDemo.onDestroy();
    }
}
