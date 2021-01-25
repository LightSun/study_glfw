package com.heaven7.android.glew.app;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import com.heaven7.core.util.PermissionHelper;

import java.lang.reflect.Constructor;

public class RenderActivity extends AppCompatActivity {

    public static final String KEY_RENDER_CLASS = "render_class";
    private PermissionHelper mHelper = new PermissionHelper(this);
    private IGLRender mRender;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        String clazz = getIntent().getStringExtra(KEY_RENDER_CLASS);
        try {
            Constructor<?> cons = Class.forName(clazz).getConstructor(Activity.class);
            mRender = (IGLRender) cons.newInstance(this);
        } catch (Exception e) {
            e.printStackTrace();
            finish();
            return;
        }

        mRender.setUp(RenderActivity.this::setViewImpl);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        mHelper.onRequestPermissionsResult(requestCode, permissions, grantResults);
    }

    private void setViewImpl(){
        GLSurfaceView view = new GLSurfaceView(this);
        view.setEGLContextClientVersion(mRender.getEGLVersion());//for GLSurfaceView often need <uses-feature android:glEsVersion="0x00020000" />
        view.setRenderer(mRender);
        view.setRenderMode(mRender.getRenderMode());
        setContentView(view);
    }
}
