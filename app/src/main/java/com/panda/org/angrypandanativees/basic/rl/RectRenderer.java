package com.panda.org.angrypandanativees.basic.rl;

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by rd0348 on 2017/11/21 0021.
 */

public class RectRenderer implements GLSurfaceView.Renderer {
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        init();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        resize(width,height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        step();
    }

    public native boolean init();
    public native void resize(int width,int height);
    public native void step();
    public native void destroy();

}
