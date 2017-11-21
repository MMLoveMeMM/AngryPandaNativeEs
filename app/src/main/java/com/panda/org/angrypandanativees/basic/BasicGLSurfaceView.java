package com.panda.org.angrypandanativees.basic;

import android.content.Context;
import android.opengl.GLSurfaceView;

import com.panda.org.angrypandanativees.basic.rl.CubeRenderer;
import com.panda.org.angrypandanativees.basic.rl.RectRenderer;
import com.panda.org.angrypandanativees.basic.rl.RendererNatives;

/**
 * Created by rd0348 on 2017/11/21 0021.
 */

public class BasicGLSurfaceView extends GLSurfaceView {

    private RendererNatives rendererNatives;

    private RectRenderer rectRenderer;

    private CubeRenderer cubeRenderer;

    public BasicGLSurfaceView(Context context) {
        super(context);
        this.setEGLContextClientVersion(3);
        setEGLConfigChooser(8,8,8,0,16,0);
        rendererNatives=new RendererNatives(context);
        rectRenderer=new RectRenderer();
        cubeRenderer=new CubeRenderer();
        this.setRenderer(cubeRenderer/*rectRenderer*//*rendererNatives*/);
        //this.setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
    }



}
