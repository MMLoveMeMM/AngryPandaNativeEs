package com.panda.org.angrypandanativees.depth;

import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.opengl.Matrix;

import com.panda.org.angrypandanativees.blend.Tangle;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by rd0348 on 2017/12/8 0008.
 */

public class DepthRenderer implements GLSurfaceView.Renderer {

    private boolean openStencilTest;
    private DTriangle mShape;

    public float yAngle;
    public float xAngle;

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        GLES20.glClearColor(0.5f, 0.5f, 0.5f, 1);
        mShape = new DTriangle();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        GLES20.glViewport(0, 0, width, height);
        Matrix.perspectiveM(mProjectionMatrix, 0, 45, (float)width/height, 2, 15);
        Matrix.setLookAtM(mViewMatrix, 0, 0, 0, 8,  0, 0, 0, 0, 1, 0);
    }

    private final float[] mProjectionMatrix = new float[16];
    private final float[] mViewMatrix = new float[16];
    private final float[] mModuleMatrix = new float[16];
    private final float[] mViewProjectionMatrix = new float[16];
    private final float[] mMVPMatrix = new float[16];

    @Override
    public void onDrawFrame(GL10 gl) {

        GLES20.glClear( GLES20.GL_DEPTH_BUFFER_BIT | GLES20.GL_COLOR_BUFFER_BIT | GLES20.GL_STENCIL_BUFFER_BIT);
        Matrix.setIdentityM(mModuleMatrix, 0);
        Matrix.rotateM(mModuleMatrix, 0, xAngle, 1, 0, 0);
        Matrix.rotateM(mModuleMatrix, 0, yAngle, 0, 1, 0);
        Matrix.multiplyMM(mViewProjectionMatrix, 0, mProjectionMatrix, 0, mViewMatrix, 0);
        Matrix.multiplyMM(mMVPMatrix, 0, mViewProjectionMatrix, 0, mModuleMatrix, 0);

        if(openStencilTest){
            GLES20.glClearDepthf(1.0f);
            GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT | GLES20.GL_DEPTH_BUFFER_BIT);
            // 开启深度测试
            GLES20.glEnable(GLES20.GL_DEPTH_TEST);
            GLES20.glDepthFunc(GLES20.GL_LESS); //基准设置为 1.0，那么GL_LESS 则深度小余 1.0 的通过测试
            //GLES20.glBlendFunc(GLES20.GL_DST_COLOR, GLES20.GL_ONE_MINUS_DST_COLOR);
            mShape.drawTrangle(mMVPMatrix);
        }else{
            // 关闭深度测试
            //GLES20.glBlendFunc(GLES20.GL_DST_COLOR, GLES20.GL_ONE_MINUS_DST_COLOR);
            mShape.drawTrangle(mMVPMatrix);
        }


    }

    public void setOpenStencilTest(boolean openStencilTest) {
        this.openStencilTest = openStencilTest;
    }

}
