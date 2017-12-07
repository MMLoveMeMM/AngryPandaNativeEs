#include "TriangleDepth.h"

const char * vertexdShaderCode = "attribute vec4 aPosition;\n"
        "attribute vec4 aColor;\n"
        "varying vec4 vColor;\n"
        "uniform mat4 uMVPMatrix;\n"
        "void main() \n"
        "{\n"
        "    gl_Position = uMVPMatrix * aPosition;\n"
        "    vColor = aColor;\n"
        "}";

const char * fragmentdShaderCode = "precision mediump float;\n"
        "varying  vec4 vColor;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = vColor;\n"
        "}";

TriangleDepth::~TriangleDepth()
{
}

TriangleDepth::TriangleDepth()
{
    initVertex();
}

void TriangleDepth::TriangleDepth::initVertex()
{

}

void TriangleDepth::initShader(const char * vertexShaderCode, const char* fragmentShaderCode)
{
    mProgram = GLUtil::createProgram(vertexdShaderCode, fragmentdShaderCode);
    mUMVPMatrixHandle = glGetUniformLocation(mProgram, "uMVPMatrix");
    mAPositionHandle = glGetAttribLocation(mProgram, "aPosition");
    mAColorHandle = glGetAttribLocation(mProgram, "aColor");
}

void TriangleDepth::initTexture()
{

}

void TriangleDepth::draw(float mvpMatrix[])
{
    glUseProgram(mProgram);
    // 将顶点数据传递到管线，顶点着色器
    glUniformMatrix4fv(mUMVPMatrixHandle, 1, GL_FALSE, mvpMatrix);

    /*
    * 注意第三个顶点z轴那个参数,由0.5改为1.5f后,观看效果,发现第三个顶点没有显示在屏幕上了
    * 准确的说是z>1.0f的点都没有显示
    */
    GLfloat mAttrArr[] =
    {
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, 0.5f, 1.5f, 0.0f, 0.0f,
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

    glEnableVertexAttribArray(mAPositionHandle);
    glEnableVertexAttribArray(mAColorHandle);
    // 绘制图元
    glDrawArrays(GL_TRIANGLE_FAN, 0, /*8*/3);

}









