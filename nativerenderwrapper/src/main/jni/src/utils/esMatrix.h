#ifndef __H_ES_MATRIX_H__
#define __H_ES_MATRIX_H__
#include "glm/mat4x4.hpp"
#include "glm/ext.hpp"
#include <iostream>
#include <stack>
using namespace std;
#ifdef __cplusplus
extern "C"{
#endif
/*
* 这个类主要用于矩阵运算
* 进行model的空间变换
*/
class GLMatrix
{
public:
    static glm::mat4 projection;
    static glm::mat4 view;
    static glm::mat4 model;

    //保护变换矩阵的栈
    static std::stack<glm::mat4> mMatrixStack;
public:
    GLMatrix();
    ~GLMatrix();

    static glm::mat4 getOrthoProjectMatrix(float left,float right,float bottom,float top,float near,float far);
    static glm::mat4 getPerspectiveProjectMatrix(float fovy, float aspect,float zNear,float zFar);

    static glm::mat4 getViewMatrix(float eyex,float eyey,float eyez,float centerx,float centery,float centerz,float upx,float upy,float upz);

    static glm::mat4 glRotation(float angle,glm::vec3 vector);
    static glm::mat4 glTranslate(glm::vec3 vector);
    static glm::mat4 glScale(glm::vec3 vector);

    static glm::mat4 glModelMatrix();

    static float* getMVPMatrix();

    static void setInitStack();//获取不变换初始矩阵

    static void pushMatrix();//保护变换矩阵

    static void popMatrix();//恢复变换矩阵
};

#ifdef __cplusplus
}
#endif

#endif //__H_ES_MATRIX_H__