#include "TriangleBuff.h"

const char * vertexbShaderCode = "attribute vec4 aPosition;\n"
        "attribute vec4 aColor;\n"
        "varying vec4 vColor;\n"
        "uniform mat4 uMVPMatrix;\n"
        "void main() \n"
        "{\n"
        "    gl_Position = uMVPMatrix * aPosition;\n"
        "    vColor = aColor;\n"
        "}";

const char * fragmentbShaderCode = "precision mediump float;\n"
        "varying  vec4 vColor;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = vColor;\n"
        "}";

TriangleBuff::~TriangleBuff()
{
    glDeleteBuffers(1, &attrBuffer);
}
TriangleBuff::TriangleBuff()
{
    initVertex();
    //initShader(vertexbShaderCode,fragmentbShaderCode);
}

void TriangleBuff::initVertex()
{
}

void TriangleBuff::initShader(const char * vertexShaderCode, const char* fragmentShaderCode)
{
    mProgram = GLUtil::createProgram(vertexbShaderCode, fragmentbShaderCode);
    mUMVPMatrixHandle = glGetUniformLocation(mProgram, "uMVPMatrix");
    mAPositionHandle = glGetAttribLocation(mProgram, "aPosition");
    mAColorHandle = glGetAttribLocation(mProgram, "aColor");
}

void TriangleBuff::initTexture()
{
    // todo nothing


}

void TriangleBuff::draw(float mvpMatrix[])
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
    glDrawArrays(GL_TRIANGLE_FAN, 0, 8);

}


