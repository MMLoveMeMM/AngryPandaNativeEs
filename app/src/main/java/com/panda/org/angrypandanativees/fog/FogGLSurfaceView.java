package com.panda.org.angrypandanativees.fog;

import android.content.Context;
import android.opengl.GLSurfaceView;

import com.panda.org.angrypandanativees.light.LightRenderer;

/**
 * Created by rd0348 on 2018/1/16 0016.
 */

public class FogGLSurfaceView extends GLSurfaceView {

    private FogRenderer mRenderer;

    public FogGLSurfaceView(Context context) {
        super(context);
        setEGLContextClientVersion(3);
        mRenderer=new FogRenderer(context);
        setRenderer(mRenderer);
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
    }
}
