package com.heaven7.android.glew.app;

public final class JNIApi {

    public static final int TYPE_ALFONS_FONT = 1;
    public static final int TYPE_LINE_RENDER = 2;

    private long mPtr;

    static {
        System.loadLibrary("studyGlfw");
    }

    public JNIApi(int type){
        mPtr = nCreate(type);
    }

    @Override
    protected void finalize() throws Throwable {
        destroy();
        super.finalize();
    }

    public long getNativePtr(){
        return mPtr;
    }

    public void init(String fontDir){
       nInit(getNativePtr(), fontDir);
    }

    public void resize(int width, int height){
        nResize(getNativePtr(), width, height);
    }
    public void draw(){
        nDraw(getNativePtr());
    }
    public void destroy(){
        if(mPtr != 0){
            nDestroy(mPtr);
            mPtr = 0;
        }
    }
    //call this to do some test. should call after resize.
    public void doTest(){
        nAfterInit(getNativePtr());
    }
    private static native long nCreate(int type);
    private static native void nInit(long ptr, String fontDir);
    private static native void nResize(long ptr, int width, int height);
    private static native void nDraw(long ptr);
    private static native void nDestroy(long mPtr);

    private static native void nAfterInit(long mPtr);
}
