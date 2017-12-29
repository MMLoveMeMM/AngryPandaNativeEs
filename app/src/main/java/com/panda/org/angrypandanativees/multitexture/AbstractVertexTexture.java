package com.panda.org.angrypandanativees.multitexture;

/**
 * Created by rd0348 on 2017/12/29 0029.
 */

public abstract class AbstractVertexTexture {
    public abstract void initVertices();
    public abstract void initShader();
    public abstract void initTexture(int type);
    public abstract void draw(int type);
}
