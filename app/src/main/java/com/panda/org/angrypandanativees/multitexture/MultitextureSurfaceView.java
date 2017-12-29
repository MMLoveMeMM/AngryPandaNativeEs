package com.panda.org.angrypandanativees.multitexture;

import android.content.Context;
import android.opengl.GLSurfaceView;

/**
 * Created by rd0348 on 2017/12/29 0029.
 */

public class MultitextureSurfaceView extends GLSurfaceView {

    private MultitextureRenderer mRenderer;

    public MultitextureSurfaceView(Context context) {
        super(context);

        setEGLContextClientVersion(3);
        mRenderer=new MultitextureRenderer(context);
        setRenderer(mRenderer);
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
    }

}
