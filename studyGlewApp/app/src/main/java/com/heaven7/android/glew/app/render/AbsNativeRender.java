package com.heaven7.android.glew.app.render;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Environment;

import com.heaven7.android.glew.app.AssetsUtils;
import com.heaven7.android.glew.app.IGLRender;
import com.heaven7.android.glew.app.JNIApi;
import com.heaven7.java.pc.schedulers.Schedulers;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public abstract class AbsNativeRender extends IGLRender {

    protected JNIApi api;
    private String dir;

    public AbsNativeRender(Activity context) {
        super(context);
    }

    public final void setNativeRenderType(int type){
        if(api != null){
            throw new RuntimeException("setNativeRenderType: can only be call once");
        }
        api = new JNIApi(type);
    }
    public void setDir(String dir) {
        this.dir = dir;
    }
    @Override
    public int getRenderMode() {
        return GLSurfaceView.RENDERMODE_WHEN_DIRTY;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        System.out.println("onSurfaceCreated");
        api.init(dir);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        System.out.println("onSurfaceChanged");
        api.resize(width, height);
        api.doTest();
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        api.draw();
    }
    @Override
    public void onDestroy() {
        api.destroy();
    }
}

 /* glClearColor(1, 1, 1, 1);
        glViewport(0, 0, width, height);

       // createShaderProgram();

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //glOrtho(0, width, 0, height, -1, 1);
        glOrthox(0, width, 0, height, -1, 1);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
