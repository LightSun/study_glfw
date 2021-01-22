package com.heaven7.android.glew.app;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.Manifest;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.os.Environment;
import android.view.View;

import com.heaven7.core.util.PermissionHelper;
import com.heaven7.java.pc.schedulers.Schedulers;

public class MainActivity extends AppCompatActivity {

    private PermissionHelper mHelper = new PermissionHelper(this);
    private FontRender mRender = new FontRender();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        mHelper.onRequestPermissionsResult(requestCode, permissions, grantResults);
    }
    private void requestPermission(){
        mHelper.startRequestPermission(Manifest.permission.WRITE_EXTERNAL_STORAGE,
                1, new PermissionHelper.ICallback() {
                    @Override
                    public void onRequestPermissionResult(String s, int i, boolean b) {
                        System.out.println("onRequestPermissionResult: " + b);
                        if(b){
                            copyFont();
                        }
                    }
                    @Override
                    public boolean handlePermissionHadRefused(String s, int i, Runnable runnable) {
                        return false;
                    }
                });
    }

    private void copyFont() {
        Schedulers.io().newWorker().schedule(new Runnable() {
            @Override
            public void run() {
                AssetsUtils.copyAll(getApplicationContext(), "fonts", Environment.getExternalStorageDirectory() + "/temp");
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        setViewImpl();
                    }
                });
            }
        });
    }
    private void setViewImpl(){
        GLSurfaceView view = new GLSurfaceView(this);
        view.setEGLContextClientVersion(3);//for GLSurfaceView often need <uses-feature android:glEsVersion="0x00020000" />
        view.setRenderer(mRender);
        mRender.setFontDir(Environment.getExternalStorageDirectory() + "/temp/fonts");
        setContentView(view);
    }

    public void onClickStart(View view) {
        requestPermission();
    }
}
