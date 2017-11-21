#ifndef __H_ES3_CUBE_H__
#define __H_ES3_CUBE_H__
#include <GLES3/gl3.h>
#include <cmath>
#include <ctime>
#include <stdlib.h>
#include "es3_shader.h"
#include "es3_utils.h"
#include "es3_matrix.h"
class es3cube
{
public:
    es3cube(){};
    ~es3cube(){};
public:
    bool init();
    void resize(int width,int height);
    void render();
    void destroy();

public:
    void matrixLoadIdentity(Matrix *result);
    void matrixMultiply(Matrix *result, Matrix *srcA, Matrix *srcB);
    void frustum(Matrix *result, float w, float h, float nearZ,
            float farZ);
    void translate(Matrix *result, GLfloat tx, GLfloat ty, GLfloat tz);
    void rotate(Matrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
    void update(float deltaTime);
private:
    GLuint program;
    GLuint positionVBO;
    GLuint colorVBO;
    GLuint mvpVBO;
    GLuint indicesIBO;
    GLfloat aspect;
    uint64_t lastFrameNs;
    GLfloat angle;

};

#endif //__H_ES3_CUBE_H__