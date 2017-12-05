#include "GLRenderer.h"
#include "glm/mat4x4.hpp"
#include "glm/ext.hpp"
#include "Triangle.h"
#include "TriangleBuff.h"
#include "TriangleTexture.h"
#include "esUtils.h"
#include "esMatrix.h"
Triangle mShape;
TriangleBuff mShapeBuff;
TriangleTexture mTriangleTexture;
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
    mTriangleTexture.initShader(NULL, NULL);
    mTriangleTexture.initTexture();

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glDisable(GL_DEPTH_TEST);
}

void GLRenderer::nativeSurfaceChanged(EGLint width, EGLint height) {
    // 正投影

    projection = GLMatrix::getOrthoProjectMatrix(-1.0f, 1.0f, width, height, 5.0f,7.0f);

    view = GLMatrix::getViewMatrix(0.0f, 0.0f, 6.0f,0.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f);
    glViewport(0, 0, width, height);
}

void GLRenderer::nativeDraw() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    model=GLMatrix::glScale(glm::vec3(0.9f));//测试缩放
    model=GLMatrix::glTranslate(glm::vec3(0.1f,0.0f,0.0f));//测试平移
    model=GLMatrix::glRotation(glm::radians(50.0f),glm::vec3(0.1f,0.0f,0.0f));//测试旋转
    glm::mat4 mvpMatrix = GLMatrix::projection * GLMatrix::view * GLMatrix::model/* * module*/;
    /*
    * 这个地方还需要看看
    */
    float *mvp = (float *) glm::value_ptr(mvpMatrix);
    // TODO
    //mShape.draw(mvp);
    //mShapeBuff.draw(mvp);
    mTriangleTexture.draw(mvp);

}