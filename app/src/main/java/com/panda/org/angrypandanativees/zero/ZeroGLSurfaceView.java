package com.panda.org.angrypandanativees.zero;

import android.content.Context;
import android.opengl.GLSurfaceView;

import com.panda.org.angrypandanativees.multitexture.MultitextureRenderer;

/**
 * Created by rd0348 on 2018/1/16 0016.
 */

public class ZeroGLSurfaceView extends GLSurfaceView {

    private ZeroRenderer mRenderer;
    public ZeroGLSurfaceView(Context context) {
        super(context);

        setEGLContextClientVersion(3);
        mRenderer=new ZeroRenderer(context);
        setRenderer(mRenderer);
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
    }

}
