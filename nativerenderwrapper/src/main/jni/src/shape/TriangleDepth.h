#ifndef __H_TRIANGLE_DEPTH_H__
#define __H_TRIANGLE_DEPTH_H__

/*
* 这个类用于深度测试
介绍 : 像素与屏幕的垂直距离，深度数值越大离屏幕越远，而深度缓存则保存了每个像素点的深度。
这就意味着：我们的立方体中，离我们观察者越远的面它的顶点的深度值就越大，
而距离我们观察者越近的面他的顶点深度值就越小。
在片段着色器中，如果遇到两个像素在屏幕上坐标相同的情况，在绘制前将会比较两者的深度（Z值），
以判断两者之间谁离观察者更近。如果新的像素深度值大于旧的顶点，则以新像素覆盖原有像素；
反之则放弃绘制新像素，保留原有像素。这个比较的过程称为深度测试(deepth testing)。

作用 : 就是把不该看到的东西剔除掉

这个测试后面重新做一下.MMP
*/
#ifdef __cplusplus
extern "C"{
#endif
#include <GLES2/gl2.h>
#include "esUtils.h"
#include <stdio.h>
#include <stdlib.h>
class TriangleDepth
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
    virtual ~TriangleDepth();
    TriangleDepth();
};

#ifdef __cplusplus
}
#endif

#endif //__H_TRIANGLE_DEPTH_H__