package com.panda.org.angrypandanativees.light;

import android.content.Context;
import android.opengl.GLSurfaceView;

/**
 * Created by rd0348 on 2018/1/16 0016.
 */

public class LightGLSurfaceView extends GLSurfaceView {

    private LightRenderer mRenderer;
    public LightGLSurfaceView(Context context) {
        super(context);

        setEGLContextClientVersion(3);
        mRenderer=new LightRenderer(context);
        setRenderer(mRenderer);
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
    }

}
