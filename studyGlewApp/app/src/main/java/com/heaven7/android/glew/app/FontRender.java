package com.heaven7.android.glew.app;

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class FontRender implements GLSurfaceView.Renderer {

    private final JNIApi api = new JNIApi();
    private String fontDir;
    private int width;
    private int height;

    public void setFontDir(String fontDir) {
        this.fontDir = fontDir;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        System.out.println("onSurfaceCreated");
        api.init(fontDir);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        System.out.println("onSurfaceChanged");
        this.width = width;
        this.height = height;
        api.resize(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        gl.glClearColor(1, 1, 1, 1);
        gl.glViewport(0, 0, width, height);

        gl.glMatrixMode(GL10.GL_PROJECTION);
        gl.glLoadIdentity();
        //glOrtho(0, width, 0, height, -1, 1);
        gl.glOrthox(0, width, 0, height, -1, 1);

        gl.glMatrixMode(GL10.GL_MODELVIEW);
        gl.glLoadIdentity();

        gl.glDisable(GL10.GL_DEPTH_TEST);
        gl.glEnable(GL10.GL_BLEND);
        gl.glBlendFunc(GL10.GL_SRC_ALPHA, GL10.GL_ONE_MINUS_SRC_ALPHA);

        api.draw();
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
