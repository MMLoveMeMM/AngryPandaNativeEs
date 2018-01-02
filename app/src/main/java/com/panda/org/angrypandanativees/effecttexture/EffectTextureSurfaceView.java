package com.panda.org.angrypandanativees.effecttexture;

import android.content.Context;
import android.opengl.GLSurfaceView;

/**
 * Created by rd0348 on 2018/1/2 0002.
 */

public class EffectTextureSurfaceView extends GLSurfaceView {

    private EffectTextureRenderer mRenderer;
    public EffectTextureSurfaceView(Context context) {
        super(context);

        this.setEGLContextClientVersion(3);
        mRenderer=new EffectTextureRenderer(context);
        this.setRenderer(mRenderer);
        this.setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);

    }

}
