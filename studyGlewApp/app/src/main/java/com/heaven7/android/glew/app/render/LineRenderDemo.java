package com.heaven7.android.glew.app.render;


import android.app.Activity;

import com.heaven7.android.glew.app.JNIApi;

public class LineRenderDemo extends AbsNativeRender {

    public LineRenderDemo(Activity context) {
        super(context);
        setNativeRenderType(JNIApi.TYPE_LINE_RENDER);
    }
}
