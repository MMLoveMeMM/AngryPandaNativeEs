#ifndef __H_ES3_MATRIX_H__
#define __H_ES3_MATRIX_H__
#include <GLES3/gl3.h>
#include <cmath>
#include <ctime>
#include <stdlib.h>
#include "es3_utils.h"
/*
* 这个矩阵算术运算,还有专门的开源包,可能更好一些
* 下次增加进来
*/

typedef struct {
    GLfloat m[MATRIX_ROW][MATRIX_COLUMN];
} Matrix;

class es3matrix
{
public:
    es3matrix();
    ~es3matrix();
public:
    static void matrixLoadIdentity(Matrix *result);
    static void matrixMultiply(Matrix *result, Matrix *srcA, Matrix *srcB);
    static void frustum(Matrix *result, float w, float h, float nearZ,
            float farZ);
    static void translate(Matrix *result, GLfloat tx, GLfloat ty, GLfloat tz);
    static void rotate(Matrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
    static void update(float deltaTime);
};

#endif //__H_ES3_MATRIX_H__