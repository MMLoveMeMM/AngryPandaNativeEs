package com.panda.org.angrypandanativees.effecttexture;

import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;

import com.panda.org.angrypandanativees.effecttexture.shape.EffectTriangleShape;
import com.panda.org.angrypandanativees.matrix.MatrixState;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by rd0348 on 2018/1/2 0002.
 */

public class EffectTextureRenderer implements GLSurfaceView.Renderer {

    private Context mContext;
    private EffectTriangleShape mEffectTriangleShape;
    public EffectTextureRenderer(Context context){
        mContext=context;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        GLES20.glClearColor(0,0,0,0);
        GLES20.glEnable(GLES20.GL_CULL_FACE);
        GLES20.glEnable(GLES20.GL_DEPTH_TEST);

        mEffectTriangleShape=new EffectTriangleShape(mContext);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        float ratio = (float)width/height;

        GLES20.glViewport(0,0,width,height);

        //调用此方法计算产生透视投影矩阵
        MatrixState.setProjectFrustum(-ratio, ratio, -1, 1, 1, 30);
        //调用此方法产生摄像机9参数位置矩阵
        MatrixState.setCamera(0,0,2,0f,0f,0f,0f,1.0f,0.0f);

            /*
            * 初始化基坐标
            * 这个作为每个物体变换的参考相对坐标起点
            * */
        MatrixState.setInitStack();
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        GLES20.glClear(GLES20.GL_DEPTH_BUFFER_BIT|GLES20.GL_COLOR_BUFFER_BIT);

        MatrixState.pushMatrix();
        mEffectTriangleShape.draw(0);
        MatrixState.popMatrix();
    }

}
