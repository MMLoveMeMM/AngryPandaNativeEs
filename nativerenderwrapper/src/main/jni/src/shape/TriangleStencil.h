#ifndef __H_TRIANGLE_STENCIL_H__
#define __H_TRIANGLE_STENCIL_H__
/*
模板缓冲测试，是指 将模版缓冲区中的值 与 一个参考值 进行比较，根据比较的结果，来对缓冲区中的值进行修改。进而决定该片段是否有效。
在应用中的体现就比如：Unity中的Mask 。

大致的工作流程：
1、第一次Draw的时候，将所有的片段都设置为不通过模版测试。然后修改模版缓冲区的值，比如+1.
2、第二次Draw的时候，给定一个值 与 模版缓冲区中的值进行比较，比如用 1 与模版缓冲区中的值进行比较 。
因为第一步中，已经+1，所以模版缓冲区中值已经是1，然后用相等 作为条件判定 模版测试通过。那么这个片段就可以绘制。
3、这样做的最终效果是，只有第一次绘制的区域，第二次绘制才可以显示。就如同Unity中的Mask，用一张图，Mask掉第二张图
*/
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