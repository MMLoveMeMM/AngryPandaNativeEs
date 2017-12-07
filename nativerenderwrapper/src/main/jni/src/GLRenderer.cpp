#include "GLRenderer.h"
#include "glm/mat4x4.hpp"
#include "glm/ext.hpp"
#include "Triangle.h"
#include "TriangleBuff.h"
#include "TriangleTexture.h"
#include "TriangleDepth.h"
#include "TriangleStencil.h"
#include "esUtils.h"
#include "esMatrix.h"
Triangle mShape;
TriangleBuff mShapeBuff;
TriangleTexture mTriangleTexture;
TriangleDepth mTriangleDepth;
TriangleStencil mTriangleStencil;
glm::mat4 projection;
glm::mat4 view;
glm::mat4 model;

void GLRenderer::nativeTexturePixels(void* pix)
{
    pixels = pix;
}

void GLRenderer::nativeSurfaceCreated() {

    //mShape.initGL(vertexShaderCode, fragmentShaderCode);
    //mShapeBuff.initShader(NULL, NULL);

    //mTriangleTexture.initShader(NULL, NULL);
    //mTriangleTexture.initTexture();
    //mTriangleDepth.initShader(NULL, NULL);

    mTriangleStencil.initShader(NULL, NULL);

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    //

    #ifdef DEF_ES_STENCIL
        glEnable(GL_STENCIL_TEST);//开启模版测试
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS); //基准设置为 1.0，那么GL_LESS 则深度小余 1.0 的通过测试
    #endif

    #if defined(DEF_ES_DEPTH)
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS); //基准设置为 1.0，那么GL_LESS 则深度小余 1.0 的通过测试
    #else
        glDisable(GL_DEPTH_TEST);
    #endif

}

void GLRenderer::nativeSurfaceChanged(EGLint width, EGLint height) {

    // 正投影
    projection = GLMatrix::getOrthoProjectMatrix(-1.0f, 1.0f, width, height, 5.0f,7.0f);

    view = GLMatrix::getViewMatrix(0.0f, 0.0f, 6.0f,0.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f);
    glViewport(0, 0, width, height);
}

void GLRenderer::nativeDraw() {

    glClearDepthf(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#ifndef DEF_ES_DEPTH
    model=GLMatrix::glScale(glm::vec3(0.9f));//测试缩放
    model=GLMatrix::glTranslate(glm::vec3(0.1f,0.0f,0.0f));//测试平移
    model=GLMatrix::glRotation(glm::radians(50.0f),glm::vec3(0.1f,0.0f,0.0f));//测试旋转
    glm::mat4 mvpMatrix = GLMatrix::projection * GLMatrix::view * GLMatrix::model * module;
#else
     glm::mat4 mvpMatrix = GLMatrix::projection * GLMatrix::view;
#endif
    /*
    * 这个地方还需要看看
    */
    float *mvp = (float *) glm::value_ptr(mvpMatrix);
    // TODO
    //mShape.draw(mvp);
    //mShapeBuff.draw(mvp);
    //mTriangleTexture.draw(mvp);
    //mTriangleDepth.draw(mvp);
    mTriangleStencil.draw(mvp);

}