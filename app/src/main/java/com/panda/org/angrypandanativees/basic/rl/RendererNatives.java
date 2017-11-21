package com.panda.org.angrypandanativees.basic.rl;

import android.content.Context;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;
import android.util.Log;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by rd0348 on 2017/11/21 0021.
 */

public class RendererNatives implements GLSurfaceView.Renderer {

    private final static String TAG = RendererNatives.class.getName();
    private AssetManager mAssetMgr = null;

    public RendererNatives(Context context){
        mAssetMgr = context.getAssets();
        if (null == mAssetMgr) {
            Log.e(TAG, "getAssets() return null !");
        }

    }

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        init();
    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int width, int height) {
        resize(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        step();
    }

    //初始化本地GLES
    public static native boolean init();
    //为本地GLES设置宽和高
    public static native void resize(int width, int height);
    //用来绘制图形
    public static native void step();

    static {
        System.loadLibrary("nativeses");
    }

}
