package com.panda.org.angrypandanativees.blendtexture.shape;

/**
 * Created by rd0348 on 2017/12/29 0029.
 */

import android.content.Context;
import android.opengl.GLES20;

import com.panda.org.angrypandanativees.R;
import com.panda.org.angrypandanativees.matrix.MatrixState;
import com.panda.org.angrypandanativees.abs.AbstractVertexTexture;
import com.panda.org.angrypandanativees.shader.ShaderParse;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

/**
 * 这里仅仅画一个四边形用于处理纹理的一些特效
 * 在x,y的平面
 */

public class BlendTriangleShape extends AbstractVertexTexture {

    private Context context;
    private int mMVPMatrixHandle;
    private int mPositionHandle;
    private int mTextureCoordsHandle;

    private int mEffectHandle;

    private int mProgram;
    private FloatBuffer vertexBuffer;
    private FloatBuffer coordBuffer;

    private int textureID;

    private float mType;

    public BlendTriangleShape(Context context) {
        this.context = context;

        initVertices();
        initTexture(0);
        initShader();

        mType=3;
    }

    public void setType(float type){
        mType=type;
    }

    @Override
    public void initVertices() {

        float[] vertices = new float[]{
                0, 0, 0,
                1, 0, 0,
                0, 1, 0,

                1, 0, 0,
                1, 1, 0,
                0, 1, 0
        };

        ByteBuffer vbb = ByteBuffer.allocateDirect(vertices.length * 4);
        vbb.order(ByteOrder.nativeOrder());
        vertexBuffer = vbb.asFloatBuffer();
        vertexBuffer.put(vertices);
        vertexBuffer.position(0);

        float[] coords = new float[]{
                0, 1,
                1, 1,
                0, 0,

                1, 1,
                1, 0,
                0, 0
        };

        ByteBuffer cbb = ByteBuffer.allocateDirect(coords.length * 4);
        cbb.order(ByteOrder.nativeOrder());
        coordBuffer = cbb.asFloatBuffer();
        coordBuffer.put(coords);
        coordBuffer.position(0);

    }

    @Override
    public void initShader() {

        String vertex_src = ShaderParse.loadFromAssetsFile("vertex_triangle_vertex.glsl", context.getResources());//
        String frag_src = ShaderParse.loadFromAssetsFile("vertex_triangle_frag.glsl", context.getResources());//

        mProgram = ShaderParse.createProgram(vertex_src, frag_src);

        mMVPMatrixHandle = GLES20.glGetUniformLocation(mProgram, "uMVPMatrix");
        mPositionHandle = GLES20.glGetAttribLocation(mProgram, "aPosition");
        mTextureCoordsHandle = GLES20.glGetAttribLocation(mProgram, "aCoordTexture");
        mEffectHandle=GLES20.glGetUniformLocation(mProgram,"uType");

    }

    @Override
    public void initTexture(int type) {

        int[] textures;

        textures = ShaderParse.initTexture(context, R.mipmap.panda);

        textureID = textures[0];
    }

    @Override
    public void draw(int type) {

        GLES20.glUseProgram(mProgram);

        GLES20.glUniformMatrix4fv(mMVPMatrixHandle, 1, false, MatrixState.getFinalMatrix(), 0);
        GLES20.glVertexAttribPointer(mPositionHandle, 3, GLES20.GL_FLOAT, false, 0, vertexBuffer);
        GLES20.glVertexAttribPointer(mTextureCoordsHandle, 2, GLES20.GL_FLOAT, false, 0, coordBuffer);

        GLES20.glUniform1f(mEffectHandle,mType);
        //GLES20.glUniform1i(mEffectHandle,mType);

        GLES20.glEnableVertexAttribArray(mPositionHandle);
        GLES20.glEnableVertexAttribArray(mTextureCoordsHandle);

        GLES20.glEnable(GLES20.GL_ACTIVE_TEXTURE);
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, textureID);
        GLES20.glActiveTexture(textureID);

        GLES20.glDrawArrays(GLES20.GL_TRIANGLES, 0, 6);

    }

}