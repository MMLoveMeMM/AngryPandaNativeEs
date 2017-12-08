package com.panda.org.angrypandanativees.stencil;

import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.opengl.Matrix;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by rd0348 on 2017/12/8 0008.
 */

public class StencilRenderer implements GLSurfaceView.Renderer {

    private boolean openStencilTest;
    private Triangle mShape;

    float yAngle;
    float xAngle;

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        GLES20.glClearColor(0.5f, 0.5f, 0.5f, 1);
        mShape = new Triangle();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        GLES20.glViewport(0, 0, width, height);
        Matrix.perspectiveM(mProjectionMatrix, 0, 45, (float)width/height, 2, 15);
        Matrix.setLookAtM(mViewMatrix, 0, 0, 0, 12,  0, 0, 0, 0, 1, 0);
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
        // 未开启模板测试
        if (!openStencilTest) {
            mShape.drawRanctangle(mMVPMatrix);
            mShape.drawTrangle(mMVPMatrix);
        } else {
            // 使用模板测试
            GLES20.glEnable(GLES20.GL_STENCIL_TEST);
            GLES20.glClear(GLES20.GL_STENCIL_BUFFER_BIT);
            GLES20.glStencilFunc(GLES20.GL_ALWAYS, 1, 0xff); // 总是通过
            GLES20.glStencilOp(GLES20.GL_KEEP, GLES20.GL_KEEP, GLES20.GL_REPLACE);
            mShape.drawRanctangle(mMVPMatrix);
            // 只有模板缓冲区中的模板值为1的地方才被绘制
            // 即如果下面绘制的三边形顶点超过上面四边形的区域,将不会被绘制,效果上全部截断,不渲染.
            GLES20.glStencilFunc(GLES20.GL_EQUAL, 1, 0xff);
            GLES20.glStencilOp(GLES20.GL_KEEP, GLES20.GL_KEEP, GLES20.GL_KEEP);
            mShape.drawTrangle(mMVPMatrix);
            GLES20.glDisable(GLES20.GL_STENCIL_TEST);
        }
    }

    public void setOpenStencilTest(boolean openStencilTest) {
        this.openStencilTest = openStencilTest;
    }
    
}
