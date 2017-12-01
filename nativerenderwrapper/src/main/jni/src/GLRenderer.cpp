#include "GLRenderer.h"
#include "glm/mat4x4.hpp"
#include "glm/ext.hpp"
#include "Triangle.h"
#include "esUtils.h"
Triangle mShape;
glm::mat4 projection;
glm::mat4 view;

const char * vertexShaderCode = "attribute vec4 aPosition;\n"
        "attribute vec4 aColor;\n"
        "varying vec4 vColor;\n"
        "uniform mat4 uMVPMatrix;\n"
        "void main() \n"
        "{\n"
        "    gl_Position = uMVPMatrix * aPosition;\n"
        "    vColor = aColor;\n"
        "}";

const char * fragmentShaderCode = "precision mediump float;\n"
        "varying  vec4 vColor;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = vColor;\n"
        "}";

void GLRenderer::nativeSurfaceCreated() {

    mShape.initGL(vertexShaderCode, fragmentShaderCode);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glDisable(GL_DEPTH_TEST);
}

void GLRenderer::nativeSurfaceChanged(EGLint width, EGLint height) {
    projection = glm::ortho(-1.0f, 1.0f, -(float) height / width, (float) height / width, 5.0f,
                            7.0f);
//    projection = glm::perspective(glm::radians(50.0f), (float)width/height, 5.0f ,7.0f);
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, 6.0f),
                       glm::vec3(0.0f, 0.0f, 0.0f),
                       glm::vec3(0.0f, 1.0f, 0.0f));
    glViewport(0, 0, width, height);
}

void GLRenderer::nativeDraw() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /*
    module = glm::rotate(module, angleX, glm::vec3(1,0,0));
    module = glm::rotate(module, angleY, glm::vec3(0,1,0));
     */
    glm::mat4 mvpMatrix = projection * view/* * module*/;
    float *mvp = (float *) glm::value_ptr(mvpMatrix);
    // TODO
    mShape.draw(mvp);
}