package com.panda.org.angrypandanativees.depth;

import android.opengl.GLES20;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

/**
 * Created by rd0348 on 2017/12/8 0008.
 */

public class DTriangle {

    private int mColorHandle;
    private int mPositionHandle;
    private int muMVPMatrixHandle;
    private FloatBuffer mtrangleBuffer;
    private int mtrangleProgram;

    public DTriangle() {
        initVetexData();
    }

    public void initVetexData() {

        float trangleVertices[] = new float[] {
                -0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
                -0.5f, 0.5f, 1.5f, 0.0f, 0.0f,
        };

        ByteBuffer lvbb = ByteBuffer.allocateDirect(trangleVertices.length * 4);
        lvbb.order(ByteOrder.nativeOrder());
        mtrangleBuffer = lvbb.asFloatBuffer();
        mtrangleBuffer.put(trangleVertices);
        mtrangleBuffer.position(0);

        int vertexShader = loaderShader(GLES20.GL_VERTEX_SHADER,
                vertexdShaderCode);
        int fragmentShader = loaderShader(GLES20.GL_FRAGMENT_SHADER,
                fragmentdShaderCode);

        mtrangleProgram = GLES20.glCreateProgram();
        GLES20.glAttachShader(mtrangleProgram, vertexShader);
        GLES20.glAttachShader(mtrangleProgram, fragmentShader);
        GLES20.glLinkProgram(mtrangleProgram);

        mPositionHandle = GLES20.glGetAttribLocation(mtrangleProgram, "aPosition");
        mColorHandle = GLES20.glGetAttribLocation(mtrangleProgram, "aColor");
        muMVPMatrixHandle = GLES20.glGetUniformLocation(mtrangleProgram, "uMVPMatrix");

    }

    public void drawTrangle(float[] mvpMatrix) {
        GLES20.glUseProgram(mtrangleProgram);

        int[] temp = new int[1];
        GLES20.glGenBuffers(1, temp,0);
        int vertexBufferHandle=temp[0];
        GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, vertexBufferHandle);
        GLES20.glBufferData(GLES20.GL_ARRAY_BUFFER, mtrangleBuffer.limit()*4, mtrangleBuffer, GLES20.GL_DYNAMIC_DRAW);

        // 将顶点数据传递到管线，顶点着色器
        GLES20.glVertexAttribPointer(mPositionHandle, 3, GLES20.GL_FLOAT,
                false, 5 * 4, 0);
        GLES20.glVertexAttribPointer(mColorHandle, 2, GLES20.GL_FLOAT,
                false, 5 * 4, 3*4);
        GLES20.glEnableVertexAttribArray(mPositionHandle);
        GLES20.glEnableVertexAttribArray(mColorHandle);
        GLES20.glUniformMatrix4fv(muMVPMatrixHandle, 1, false, mvpMatrix, 0);
        // 绘制图元
        GLES20.glDrawArrays(GLES20.GL_TRIANGLES, 0, 3);

        GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, 0);
        GLES20.glDisableVertexAttribArray(mPositionHandle);
        GLES20.glDisableVertexAttribArray(mColorHandle);

    }

    private int loaderShader(int type, String shaderCode) {
        int shader = GLES20.glCreateShader(type);
        GLES20.glShaderSource(shader, shaderCode);
        GLES20.glCompileShader(shader);
        return shader;
    }

    final static String vertexdShaderCode = "attribute vec4 aPosition;"
            + "attribute vec4 aColor;"
            + "varying vec4 vColor;"
            + "uniform mat4 uMVPMatrix;"
            + "void main()"
            + "{"
            + "    gl_Position = uMVPMatrix * aPosition;"
            + "    vColor = aColor;"
            + "}";

    final static String fragmentdShaderCode = "precision mediump float;"
            + "varying  vec4 vColor;"
            + "void main()"
            + "{"
            + "    gl_FragColor = vColor;"
            + "}";
}
