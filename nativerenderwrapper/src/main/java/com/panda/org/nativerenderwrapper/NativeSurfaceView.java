package com.panda.org.nativerenderwrapper;

import android.content.Context;
import android.graphics.Bitmap;
import android.view.MotionEvent;
import android.view.Surface;
import android.view.SurfaceView;
import android.view.SurfaceHolder;

/**
 * Created by rd0348 on 2017/11/30 0030.
 */

public class NativeSurfaceView extends SurfaceView implements SurfaceHolder.Callback {

    public NativeSurfaceView(Context context) {
        super(context);
        getHolder().addCallback(this);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        nativeRequestRender();//开始显示
        return super.onTouchEvent(event);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        nativeStartRender();
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        // ANativeWindow 需要上层将surface对象传入用于覆盖图形数据
        nativeSurfaceChanged(holder.getSurface());
    }

    public void surfaceDestroyed() {
        // ANativeWindow 需要上层将surface对象传入用于覆盖图形数据
        nativeSurfaceDestroyed();
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        nativeSurfaceDestroyed();
    }

    private static native void nativeSurfaceChanged(Surface surface);

    private static native void nativeSurfaceDestroyed();

    private static native void nativeStartRender();

    private static native void nativeStartTextureRender(Bitmap bitmap);//带一张纹理图下去

    private static native void nativeRequestRender();
    static {
        System.loadLibrary("nativerenderer");
    }

}
