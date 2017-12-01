#ifndef __H_TRIANGLE_H__
#define __H_TRIANGLE_H__
#ifdef __cplusplus
extern "C"{
#endif
#include<math.h>
#include <GLES2/gl2.h>
#include "esUtils.h"
#define PI 3.1415926
class Triangle {
public:
    GLint mProgram;
    GLint mUMVPMatrixHandle;
    GLint mAPositionHandle;
    GLint mAColorHandle;
    GLfloat* mVertexArray;
    GLfloat* mColorArray;

    void initVertex();
    void initGL(const char * vertexShaderCode, const char* fragmentShaderCode);
    void draw(float mvpMatrix[]);
    virtual ~Triangle();
    Triangle();
};

#ifdef __cplusplus
}
#endif

#endif //__H_TRIANGLE_H__