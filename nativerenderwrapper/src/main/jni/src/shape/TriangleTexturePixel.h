#ifndef __H_TRIANGLE_TEXTURE_PIXEL_H__
#define __H_TRIANGLE_TEXTURE_PIXEL_H__
#ifdef __cplusplus
extern "C"{
#endif

class TriangleTexturePixel
{
public:
    TriangleTexturePixel();
    ~TriangleTexturePixel();

    GLint mProgram;
    GLint mUMVPMatrixHandle;
    GLint mAPositionHandle;
    GLint mAColorHandle;
    GLint mACoordHandle;
    GLuint attrBuffer;
    GLuint textureId;

    void initVertex();
    void initShader(const char * vertexShaderCode, const char* fragmentShaderCode);
    void initTexture(void* pixels);
    void draw(float mvpMatrix[]);

};

#ifdef __cplusplus
}
#endif
#endif //__H_TRIANGLE_TEXTURE_PIXEL_H__