#ifndef __H_TRIANGLE_TEXTURE_H__
#define __H_TRIANGLE_TEXTURE_H__
#include "glm/mat4x4.hpp"
#include "glm/ext.hpp"
#ifdef __cplusplus
extern "C"{
#endif
#include<math.h>
#include <GLES2/gl2.h>
#include "esUtils.h"
#include <stdio.h>
#include <stdlib.h>
#define PI 3.1415926
class TriangleTexture
{
public:

    GLint mProgram;
    GLint mUMVPMatrixHandle;
    GLint mAPositionHandle;
    GLint mAColorHandle;
    GLint mACoordHandle;
    GLuint attrBuffer;
    GLuint textureId;

    void initVertex();
    void initShader(const char * vertexShaderCode, const char* fragmentShaderCode);
    void initTexture();
    void draw(float mvpMatrix[]);
    virtual ~TriangleTexture();
    TriangleTexture();
};

#ifdef __cplusplus
}
#endif
#endif //__H_TRIANGLE_TEXTURE_H__