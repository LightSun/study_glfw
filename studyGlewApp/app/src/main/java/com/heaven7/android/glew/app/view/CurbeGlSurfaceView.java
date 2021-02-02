package com.heaven7.android.glew.app.view;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

import com.heaven7.android.glew.app.render.CurbeRender;

/*
 * simple extention of the GLsurfaceview.  basically setup to use opengl 3.0
 * and set some configs.  This would be where the touch listener is setup to do something.
 *
 * It also declares and sets the render.
 */

public class CurbeGlSurfaceView extends GLSurfaceView {
    IRender curbeRender;

    public CurbeGlSurfaceView(Context context) {
        super(context);
        super.setEGLConfigChooser(8, 8, 8, 8, 16, 0);
    }

    @Override
    public void setRenderer(Renderer renderer) {
        super.setRenderer(renderer);
        curbeRender = (IRender) renderer;
    }

    //private final float TOUCH_SCALE_FACTOR = 180.0f / 320;
    private static final float TOUCH_SCALE_FACTOR = 0.015f;
    private float mPreviousX;
    private float mPreviousY;

    @Override
    public boolean onTouchEvent(MotionEvent e) {
        // MotionEvent reports input details from the touch screen
        // and other input controls. In this case, you are only
        // interested in events where the touch position changed.

        float x = e.getX();
        float y = e.getY();

        switch (e.getAction()) {
            case MotionEvent.ACTION_MOVE:

                float dx = x - mPreviousX;
                //subtract, so the cube moves the same direction as your finger.
                //with plus it moves the opposite direction.
                curbeRender.setX(curbeRender.getX() - (dx * TOUCH_SCALE_FACTOR));

                float dy = y - mPreviousY;
                curbeRender.setY(curbeRender.getY() - (dy * TOUCH_SCALE_FACTOR));
        }

        mPreviousX = x;
        mPreviousY = y;
        return true;
    }

    public interface IRender{

        float getX();
        float getY();

        void setX(float v);
        void setY(float v);
    }
}
