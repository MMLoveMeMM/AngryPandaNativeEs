package com.panda.org.angrypandanativees.blendtexture;

import android.content.Context;
import android.opengl.GLSurfaceView;

/**
 * Created by rd0348 on 2017/12/29 0029.
 */

public class BlendTextureSurfaceView extends GLSurfaceView {

    private BlendTextureRenderer mRenderer;

    public BlendTextureSurfaceView(Context context) {
        super(context);

        setEGLContextClientVersion(3);
        mRenderer=new BlendTextureRenderer(context);
        setRenderer(mRenderer);
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);

    }

}
