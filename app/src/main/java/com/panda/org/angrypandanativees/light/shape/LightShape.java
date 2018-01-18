package com.panda.org.angrypandanativees.light.shape;

import android.content.Context;
import android.opengl.GLES20;

import com.panda.org.angrypandanativees.abs.AbstractVertexTexture;
import com.panda.org.angrypandanativees.matrix.MatrixState;
import com.panda.org.angrypandanativees.shader.ShaderParse;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.util.ArrayList;

/**
 * Created by rd0348 on 2018/1/16 0016.
 */

public class LightShape extends AbstractVertexTexture {

    private static final float r=0.8f;

    private static final float LIGHT[]={1.0f, 0.5f, 1.5f}; // 光线向量
    private static final float CAMERA[]={0.0f, 0f, 3f}; // 相机位置

    private int vCount;
    private Context context;
    private FloatBuffer fbVertex;
    private FloatBuffer fbNormal;
    private FloatBuffer fbLight;
    private FloatBuffer fbCamera;

    int mProgram;   // 自定义渲染管线程序id

    int muMVPMatrixHandle;// 总变换矩阵引用id
    int maPositionHandle; // 顶点位置属性引用id
    int maNormalHandle; // 顶点法向量属性引用
    int maLightLocationHandle;// 光源位置属性引用
    int maCameraHandle;// 相机位置属性引用

    public LightShape(Context ctx){
        context=ctx;
        initVertices();
        initTexture(0);
        initShader();
    }

    @Override
    public void initVertices() {

        ArrayList<Float> alVertix = new ArrayList<Float>();
        final int angleSpan = 10;// 将球进行单位切分的角度
        for (int vAngle = -90; vAngle < 90; vAngle = vAngle + angleSpan)// 垂直方向angleSpan度一份
        {
            for (int hAngle = 0; hAngle <= 360; hAngle = hAngle + angleSpan)// 水平方向angleSpan度一份
            {
                float x0 = (float) (r * Math.cos(Math.toRadians(vAngle)) * Math.cos(Math.toRadians(hAngle)));
                float y0 = (float) (r * Math.cos(Math.toRadians(vAngle)) * Math.sin(Math.toRadians(hAngle)));
                float z0 = (float) (r * Math.sin(Math.toRadians(vAngle)));

                float x1 = (float) (r * Math.cos(Math.toRadians(vAngle)) * Math.cos(Math.toRadians(hAngle + angleSpan)));
                float y1 = (float) (r * Math.cos(Math.toRadians(vAngle)) * Math.sin(Math.toRadians(hAngle + angleSpan)));
                float z1 = (float) (r * Math.sin(Math.toRadians(vAngle)));

                float x2 = (float) (r * Math.cos(Math.toRadians(vAngle + angleSpan)) * Math.cos(Math.toRadians(hAngle + angleSpan)));
                float y2 = (float) (r * Math.cos(Math.toRadians(vAngle + angleSpan)) * Math.sin(Math.toRadians(hAngle + angleSpan)));
                float z2 = (float) (r * Math.sin(Math.toRadians(vAngle + angleSpan)));

                float x3 = (float) (r * Math.cos(Math.toRadians(vAngle + angleSpan)) * Math.cos(Math.toRadians(hAngle)));
                float y3 = (float) (r * Math.cos(Math.toRadians(vAngle + angleSpan)) * Math.sin(Math.toRadians(hAngle)));
                float z3 = (float) (r * Math.sin(Math.toRadians(vAngle + angleSpan)));

                alVertix.add(x1);
                alVertix.add(y1);
                alVertix.add(z1);
                alVertix.add(x3);
                alVertix.add(y3);
                alVertix.add(z3);
                alVertix.add(x0);
                alVertix.add(y0);
                alVertix.add(z0);

                alVertix.add(x1);
                alVertix.add(y1);
                alVertix.add(z1);
                alVertix.add(x2);
                alVertix.add(y2);
                alVertix.add(z2);
                alVertix.add(x3);
                alVertix.add(y3);
                alVertix.add(z3);

            }
        }

        vCount = alVertix.size() / 3;
        float vertices[] = new float[alVertix.size()];
        for (int i = 0; i < vertices.length; i++) {
            vertices[i] = alVertix.get(i);
        }

        ByteBuffer bbv = ByteBuffer.allocateDirect(vertices.length * 4);
        bbv.order(ByteOrder.nativeOrder());
        fbVertex = bbv.asFloatBuffer();
        fbVertex.put(vertices);
        fbVertex.position(0);

        ByteBuffer bbn = ByteBuffer.allocateDirect(vertices.length * 4);
        bbn.order(ByteOrder.nativeOrder());
        fbNormal = bbn.asFloatBuffer();
        fbNormal.put(vertices);
        fbNormal.position(0);

        ByteBuffer bbl = ByteBuffer.allocateDirect(LIGHT.length * 4);
        bbl.order(ByteOrder.nativeOrder());
        fbLight = bbl.asFloatBuffer();
        fbLight.put(LIGHT);
        fbLight.position(0);

        ByteBuffer bbc = ByteBuffer.allocateDirect(CAMERA.length * 4);
        bbc.order(ByteOrder.nativeOrder());
        fbCamera = bbc.asFloatBuffer();
        fbCamera.put(CAMERA);
        fbCamera.position(0);


    }

    @Override
    public void initShader() {

        /*
        * light_triangle_vertex : 反射光影响
        * light1_triangle_vertex : 三种光源
        * light2_triangle_vertex : 仅仅环境光
        * */
        String vertex_src = ShaderParse.loadFromAssetsFile("light2_triangle_vertex.glsl", context.getResources());//
        String frag_src = ShaderParse.loadFromAssetsFile("light2_triangle_frag.glsl", context.getResources());//

        mProgram = ShaderParse.createProgram(vertex_src, frag_src);

        maPositionHandle = GLES20.glGetAttribLocation(mProgram, "aPosition");
        muMVPMatrixHandle = GLES20.glGetUniformLocation(mProgram, "uMVPMatrix");

        maNormalHandle= GLES20.glGetAttribLocation(mProgram, "aNormal");
        maLightLocationHandle=GLES20.glGetUniformLocation(mProgram, "uLightLocation");
        //TODO 添加相机引用
        maCameraHandle=GLES20.glGetUniformLocation(mProgram, "uCamera");
    }

    @Override
    public void initTexture(int type) {

    }

    @Override
    public void draw(int type) {

        GLES20.glUseProgram(mProgram);

        GLES20.glUniformMatrix4fv(muMVPMatrixHandle, 1, false, MatrixState.getFinalMatrix(), 0);

        GLES20.glUniform3fv(maLightLocationHandle, 1, fbLight);
        //TODO 添加相机位置
        GLES20.glUniform3fv(maCameraHandle, 1, fbCamera);

        GLES20.glVertexAttribPointer(maPositionHandle, 3, GLES20.GL_FLOAT, false, 3 * 4, fbVertex);
        GLES20.glVertexAttribPointer(maNormalHandle, 3, GLES20.GL_FLOAT, false, 3 * 4, fbNormal);

        GLES20.glEnableVertexAttribArray(maPositionHandle);
        GLES20.glEnableVertexAttribArray(maNormalHandle);

        GLES20.glDrawArrays(GLES20.GL_TRIANGLES, 0, vCount);

    }

}
