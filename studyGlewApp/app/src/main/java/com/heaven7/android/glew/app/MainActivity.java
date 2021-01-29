package com.heaven7.android.glew.app;

import android.Manifest;
import android.os.Bundle;

import com.heaven7.android.glew.app.render.AirHockeyRenderer;
import com.heaven7.android.glew.app.render.FillRender;
import com.heaven7.android.glew.app.render.FontRender;
import com.heaven7.android.glew.app.render.LightDemoRender;
import com.heaven7.android.glew.app.render.LineRenderDemo;
import com.heaven7.core.util.BundleHelper;
import com.heaven7.core.util.PermissionHelper;

import java.util.List;

public class MainActivity extends AbsMainActivity {

    private final PermissionHelper mHelper = new PermissionHelper(this);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestPermission();
    }

    private void requestPermission(){
        mHelper.startRequestPermission(Manifest.permission.WRITE_EXTERNAL_STORAGE,
                1, new PermissionHelper.ICallback() {
                    @Override
                    public void onRequestPermissionResult(String s, int i, boolean b) {
                        System.out.println("onRequestPermissionResult: " + b);
                        if(b){

                        }
                    }
                    @Override
                    public boolean handlePermissionHadRefused(String s, int i, Runnable runnable) {
                        return false;
                    }
                });
    }

    public void addRenderDemo(Class<? extends IGLRender> render, String desc){
        ActivityInfo info = new ActivityInfo(RenderActivity.class, desc);
        info.setArgs(new BundleHelper().putString(RenderActivity.KEY_RENDER_CLASS,
                render.getName()).getBundle());
        mInfos.add(info);
    }

    @Override
    protected void addDemos(List<ActivityInfo> list) {
        addRenderDemo(FontRender.class, "Font render demo");
        addRenderDemo(LineRenderDemo.class, "Line render demo");
        addRenderDemo(LightDemoRender.class, "light render demo");
        addRenderDemo(AirHockeyRenderer.class, "AirHockeyRenderer demo");
        addRenderDemo(FillRender.class, "FillRender demo");
    }
}
