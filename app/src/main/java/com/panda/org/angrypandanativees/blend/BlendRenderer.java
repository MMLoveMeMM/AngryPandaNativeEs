package com.panda.org.angrypandanativees.blend;

import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.opengl.Matrix;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by rd0348 on 2017/12/8 0008.
 */

public class BlendRenderer implements GLSurfaceView.Renderer {

    private boolean openStencilTest;
    private Tangle mShape;

    public float yAngle;
    public float xAngle;

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        GLES20.glClearColor(0.5f, 0.5f, 0.5f, 1);
        mShape = new Tangle();
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
            // 开启混合
            // 开启混合后,重叠的片源颜色将重叠混合
            mShape.drawRanctangle(mMVPMatrix);

            GLES20.glEnable(GLES20.GL_BLEND);
            GLES20.glBlendFunc(GLES20.GL_DST_COLOR, GLES20.GL_ONE_MINUS_DST_COLOR);

            mShape.drawTrangle(mMVPMatrix);
            GLES20.glDisable(GLES20.GL_BLEND);
        }else{
            // 关闭混合
            mShape.drawRanctangle(mMVPMatrix);
            GLES20.glBlendFunc(GLES20.GL_DST_COLOR, GLES20.GL_ONE_MINUS_DST_COLOR);
            mShape.drawTrangle(mMVPMatrix);
        }


    }

    public void setOpenStencilTest(boolean openStencilTest) {
        this.openStencilTest = openStencilTest;
    }

}
