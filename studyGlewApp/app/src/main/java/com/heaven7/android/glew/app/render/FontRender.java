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

public class FontRender extends AbsNativeRender {

    public FontRender(Activity context) {
        super(context);
        setNativeRenderType(JNIApi.TYPE_ALFONS_FONT);
    }

    @Override
    public void setUp(Runnable next) {
        setDir(Environment.getExternalStorageDirectory() + "/temp/fonts/");
        Schedulers.io().newWorker().schedule(new Runnable() {
            @Override
            public void run() {
                AssetsUtils.copyAll(context.getApplicationContext(), "fonts", Environment.getExternalStorageDirectory() + "/temp");
                context.runOnUiThread(next);
            }
        });
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
