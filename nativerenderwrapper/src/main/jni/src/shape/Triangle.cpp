#include "Triangle.h"
const char * vertexShaderCode = "attribute vec4 aPosition;\n"
        "attribute vec4 aColor;\n"
        "varying vec4 vColor;\n"
        "uniform mat4 uMVPMatrix;\n"
        "void main() \n"
        "{\n"
        "    gl_Position = uMVPMatrix * aPosition;\n"
        "    vColor = aColor;\n"
        "}";

const char * fragmentShaderCode = "precision mediump float;\n"
        "varying  vec4 vColor;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = vColor;\n"
        "}";

Triangle::Triangle()
{
    initVertex();
    initShader(vertexShaderCode,fragmentShaderCode);
}

Triangle::~Triangle()
{
    delete [] mVertexArray;
    delete [] mColorArray;
}

void Triangle::initVertex()
{
    mVertexArray = new GLfloat[3*8];
    mColorArray = new GLfloat[8*4];
    int j = 0, k = 0;
    mVertexArray[j++] = 0;
    mVertexArray[j++] = 0;
    mVertexArray[j++] = 0;

    mColorArray[k++] = 1;
    mColorArray[k++] = 1;
    mColorArray[k++] = 1;
    mColorArray[k++] = 0;
    for (int angle = 0; angle <= 360; angle += 60) {
        mVertexArray[j++] = (GLfloat) (cos(PI * angle / 180));
        mVertexArray[j++] = (GLfloat) (sin(PI * angle / 180));
        mVertexArray[j++] = 0;

        mColorArray[k++] = 1;
        mColorArray[k++] = 0;
        mColorArray[k++] = 0;
        mColorArray[k++] = 0;
    }

}

void Triangle::initShader(const char * vertexShaderCode, const char* fragmentShaderCode)
{
    mProgram = GLUtil::createProgram(vertexShaderCode, fragmentShaderCode);
    mUMVPMatrixHandle = glGetUniformLocation(mProgram, "uMVPMatrix");
    mAPositionHandle = glGetAttribLocation(mProgram, "aPosition");
    mAColorHandle = glGetAttribLocation(mProgram, "aColor");
}

void Triangle::draw(float mvpMatrix[])
{
    glUseProgram(mProgram);
    // 将顶点数据传递到管线，顶点着色器
    glUniformMatrix4fv(mUMVPMatrixHandle, 1, GL_FALSE, mvpMatrix);
    glVertexAttribPointer(mAPositionHandle, 3, GL_FLOAT, GL_FALSE, 3 * 4, mVertexArray);
    // 将顶点颜色传递到管线，顶点着色器
    glVertexAttribPointer(mAColorHandle, 4, GL_FLOAT, GL_FALSE, 4*4, mColorArray);

    glEnableVertexAttribArray(mAPositionHandle);
    glEnableVertexAttribArray(mAColorHandle);
    // 绘制图元
    glDrawArrays(GL_TRIANGLE_FAN, 0, 8);
}
