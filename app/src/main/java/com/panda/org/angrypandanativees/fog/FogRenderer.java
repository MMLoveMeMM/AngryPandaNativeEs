package com.panda.org.angrypandanativees.fog;

import android.content.Context;
import android.opengl.GLSurfaceView;

import com.panda.org.angrypandanativees.fog.shape.FogShape;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by rd0348 on 2018/1/16 0016.
 */

public class FogRenderer implements GLSurfaceView.Renderer {

    private FogShape mFogShape;
    private Context context;

    public FogRenderer(Context ctx){

        context=ctx;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

        mFogShape=new FogShape(context);


    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {

    }

    @Override
    public void onDrawFrame(GL10 gl) {

    }

}
