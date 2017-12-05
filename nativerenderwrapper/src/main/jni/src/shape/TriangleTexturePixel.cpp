#include "TriangleTexturePixel.h"

const char* vertexbtShader=
{
    "uniform mat4 m_mvp;\n"
    "attribute vec3 m_position;\n"
    "attribute vec4 m_color;\n"
    "attribute vec2 m_uv;\n"

    "varying vec4 m_outColor;\n"
    "varying vec2 m_outUV;\n"

    "void main()\n"
    "{\n"
    "   vec4 pos=vec4(m_position,1);\n"
    "   gl_Position=m_mvp*pos;\n"
    "   m_outColor=m_color;\n"
    "   m_outUV=m_uv;\n"
    "}"
};

const char* fragmentbtShader =
{
    "precision lowp float;\n"
    "uniform sampler2D m_texture;\n"

    "varying vec4 m_outColor;\n"
    "varying vec2 m_outUV;\n"

    "void main()\n"
    "{\n"
    "   gl_FragColor=m_outColor*texture2D(m_texture,m_outUV);\n"
    "}"
};

TriangleTexturePixel::TriangleTexturePixel()
{
    initVertex();
}
TriangleTexturePixel::~TriangleTexturePixel()
{
}

void TriangleTexturePixel::initVertex()
{
}
void TriangleTexturePixel::initShader(const char * vertexShaderCode, const char* fragmentShaderCode)
{
    mProgram = GLUtil::createProgram(vertextShader, fragmenttShader);
    mUMVPMatrixHandle = glGetUniformLocation(mProgram, "m_mvp");
    mAPositionHandle = glGetAttribLocation(mProgram, "m_position");
    mAColorHandle = glGetAttribLocation(mProgram, "m_color");
    mACoordHandle = glGetAttribLocation(mProgram, "m_uv");
}
void TriangleTexturePixel::initTexture(void* pixels)
{
    // 2x2 Image, 3 bytes per pixel (R, G, B)
    /*GLubyte pixels[4 * 3] =
    {
      255,   0,   0, // Red
        0, 255,   0, // Green
        0,   0, 255, // Blue
      255, 255,   0  // Yellow
    };*/

    // Use tightly packed data
    glPixelStorei (GL_UNPACK_ALIGNMENT, 1 );

    // Generate a texture object
    glGenTextures ( 1, &textureId );

    // Bind the texture object
    glBindTexture ( GL_TEXTURE_2D, textureId );

    // Load the texture
    glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    // Set the filtering mode
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void TriangleTexturePixel::draw(float mvpMatrix[])
{
    glUseProgram(mProgram);
    // 将顶点数据传递到管线，顶点着色器
    glUniformMatrix4fv(mUMVPMatrixHandle, 1, GL_FALSE, mvpMatrix);

    /*
    * 采用缓存数据的方式加载数据
    * 这个可以对比Triangle.cpp类的做法
    */
    GLfloat mAttrArr[] = {
        0.5f, -0.5f, -1.0f,     1.0f, 0.0f,
        -0.5f, 0.5f, -1.0f,     0.0f, 1.0f,
        -0.5f, -0.5f, -1.0f,    0.0f, 0.0f,
        0.5f, 0.5f, -1.0f,      1.0f, 1.0f,
        -0.5f, 0.5f, -1.0f,     0.0f, 1.0f,
        0.5f, -0.5f, -1.0f,     1.0f, 0.0f,
    };

    glm::vec2 uv[] =
    {
        glm::vec2(1.0f, 0.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 0.0f)
    };

    glGenBuffers(1, &attrBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, attrBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mAttrArr), mAttrArr, GL_DYNAMIC_DRAW);
    /*
    * 注意下面取数的方式
    * (float *)NULL + 3 : 每次取出5个数据后,从这五个数的第四个数开始取数来使用,2 : 代表取出来个数据
    */
    glVertexAttribPointer(mAPositionHandle, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*5, NULL);
    // 将顶点颜色传递到管线，顶点着色器
    glVertexAttribPointer(mAColorHandle, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (float *)NULL + 3);

    glActiveTexture (GL_TEXTURE0);
    glBindTexture (GL_TEXTURE_2D, textureId);
    glVertexAttribPointer(mACoordHandle, 2, GL_FLOAT, false, sizeof(glm::vec2), uv);

    glEnableVertexAttribArray(mAPositionHandle);
    glEnableVertexAttribArray(mAColorHandle);
    glEnableVertexAttribArray(mACoordHandle);
    // 绘制图元
    glDrawArrays(GL_TRIANGLE_FAN, 0, 8);
}