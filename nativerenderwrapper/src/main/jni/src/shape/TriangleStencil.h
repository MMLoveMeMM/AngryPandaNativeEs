#ifndef __H_TRIANGLE_STENCIL_H__
#define __H_TRIANGLE_STENCIL_H__

#ifdef __cplusplus
extern "C"{
#endif
#include <GLES2/gl2.h>
#include "esUtils.h"
#include <stdio.h>
#include <stdlib.h>
class TriangleStencil
{
public:
    GLint mProgram;
    GLint mUMVPMatrixHandle;
    GLint mAPositionHandle;
    GLint mAColorHandle;
    GLuint attrBuffer;
    GLuint textureId;

    void initVertex();
    void initShader(const char* vertexShaderCode, const char* fragmentShaderCode);
    void initTexture();
    void draw(float mvpMatrix[]);
    virtual ~TriangleStencil();
    TriangleStencil();

private:
    int mCount=0;
};

#ifdef __cplusplus
}
#endif

#endif //__H_TRIANGLE_STENCIL_H__