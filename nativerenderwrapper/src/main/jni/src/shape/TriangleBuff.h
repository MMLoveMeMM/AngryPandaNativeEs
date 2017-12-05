#ifndef __H_TRIANGLE_BUFF_H__
#define __H_TRIANGLE_BUFF_H__

#ifdef __cplusplus
extern "C"{
#endif
#include<math.h>
#include <GLES2/gl2.h>
#include "esUtils.h"
#include <stdio.h>
#include <stdlib.h>
#define PI 3.1415926
class TriangleBuff {
public:
    GLint mProgram;
    GLint mUMVPMatrixHandle;
    GLint mAPositionHandle;
    GLint mAColorHandle;
    GLuint attrBuffer;
    GLuint textureId;

    void initVertex();
    void initShader(const char * vertexShaderCode, const char* fragmentShaderCode);
    void initTexture();
    void draw(float mvpMatrix[]);
    virtual ~TriangleBuff();
    TriangleBuff();
};

#ifdef __cplusplus
}
#endif
#endif //__H_TRIANGLE_BUFF_H__