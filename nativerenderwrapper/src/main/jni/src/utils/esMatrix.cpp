#include "esMatrix.h"

glm::mat4 GLMatrix::projection=glm::mat4(1.0);
glm::mat4 GLMatrix::view=glm::mat4(1.0);
glm::mat4 GLMatrix::model=glm::mat4(1.0);
std::stack<glm::mat4> GLMatrix::mMatrixStack;
GLMatrix::GLMatrix()
{
}

GLMatrix::~GLMatrix()
{
}

glm::mat4 GLMatrix::getOrthoProjectMatrix(float left,float right,float bottom,float top,float near,float far)
{
    projection = glm::ortho(left, right, -(float) top / bottom, (float) top / bottom, near,far);
    return projection;
}

glm::mat4 GLMatrix::getPerspectiveProjectMatrix(float fovy, float aspect,float near,float far)
{
    projection = glm::perspective(glm::radians(/*50.0f*/fovy), aspect/*(float)width/height*/, near ,far);
    return projection;
}

glm::mat4 GLMatrix::getViewMatrix(float eyex,float eyey,float eyez,float centerx,float centery,float centerz,float upx,float upy,float upz)
{
    view = glm::lookAt(glm::vec3(eyex, eyey, eyez), // 相机
                           glm::vec3(centerx, centery, centerz), // 物体坐标
                           glm::vec3(upx, upy, upz)); // 相机法线
    return view;
}

glm::mat4 GLMatrix::glRotation(float angle,glm::vec3 vector)
{
    model = glm::rotate(model, angle, vector/*glm::vec3(0.0, 1.0, 0.0)*/);
    return model;
}
glm::mat4 GLMatrix::glTranslate(glm::vec3 vector)
{
    model = glm::translate(model, vector/*glm::vec3(10.0, 0.0, 0.0)*/);
    return model;
}
glm::mat4 GLMatrix::glScale(glm::vec3 vector)
{
    model = glm::scale(model, vector/*glm::vec3(2.0)*/);
    return model;
}

glm::mat4 GLMatrix::glModelMatrix()
{
    return model;
}

float* GLMatrix::getMVPMatrix()
{
    glm::mat4 mvpMatrix = projection*view*model;
    return (float *) glm::value_ptr(mvpMatrix);
}

void GLMatrix::setInitStack()//获取不变换初始矩阵
{
    // 直接使用了stl的堆栈stack类
    // 暂时不需要初始化
}

void GLMatrix::pushMatrix()//保护变换矩阵
{
    mMatrixStack.push(model);
}

void GLMatrix::popMatrix()//恢复变换矩阵
{
    model = mMatrixStack.top();
    mMatrixStack.pop();
}
