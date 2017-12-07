#include "TriangleStencil.h"
#include "glm/mat4x4.hpp"
#include "glm/ext.hpp"
const char * vertexsShaderCode = "attribute vec4 aPosition;\n"
        "attribute vec4 aColor;\n"
        "varying vec4 vColor;\n"
        "uniform mat4 uMVPMatrix;\n"
        "void main() \n"
        "{\n"
        "    gl_Position = uMVPMatrix * aPosition;\n"
        "    vColor = aColor;\n"
        "}";

const char * fragmentsShaderCode = "precision mediump float;\n"
        "varying  vec4 vColor;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = vColor;\n"
        "}";

const char* vertexsShader=
		{
			"precision lowp float;\n"
			"uniform mat4 m_mvp;\n"
			"attribute vec4 m_position;\n"
			"attribute vec4 m_color;\n"
			"varying vec4 m_outColor;\n"
			"void main()\n"
			"{\n"
			"	vec4 pos=m_position;\n"
			"	gl_Position=m_mvp*pos;\n"
			"	m_outColor=m_color;\n"
			"}"
		};

		const char* fragmentsShader =
		{
			"precision lowp float;\n"
			"varying vec4 m_outColor;\n"
			"void main()\n"
			"{\n"
			"	gl_FragColor=m_outColor;\n"
			"}"
		};

TriangleStencil::~TriangleStencil()
{

}

TriangleStencil::TriangleStencil()
{
    initVertex();
}

void TriangleStencil::initVertex()
{

}

void TriangleStencil::initShader(const char* vertexShaderCode, const char* fragmentShaderCode)
{
    mProgram = GLUtil::createProgram(vertexsShader, fragmentsShader);
    mUMVPMatrixHandle = glGetUniformLocation(mProgram, "m_mvp");
    mAPositionHandle = glGetAttribLocation(mProgram, "m_position");
    mAColorHandle = glGetAttribLocation(mProgram, "m_color");
}

void TriangleStencil::initTexture()
{

}
/*
* 下面的代码参考 : http://blog.csdn.net/huutu/article/details/53209332
*/
void TriangleStencil::draw(float mvpMatrix[])
{
    glUseProgram(mProgram);

    glClearColor(0, 0, 0, 1.0);
    glClearDepthf(1.0f);//深度测试的基准,注意1.0代表从近裁剪面到远裁剪面 这一段范围！！并不是指Z轴的1个单位
    glClearStencil(0);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT |GL_STENCIL_BUFFER_BIT);
    //width : 1080, height : 1548
    glViewport(0, 0, 1080, 1548);
    //model;
    glm::mat4 model = glm::mat4(1.0f);

    //View
    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, -10.0f), glm::vec3(0, 0,0), glm::vec3(0, 1, 0));

    //透视 注意近裁剪面 远裁剪面的值是相对于Camera Position的 这里Camera位于Z -10，那么近裁剪面是 0，远裁剪面是2.
    glm::mat4 proj = glm::perspective(glm::radians(60.0f), 1.0f, 10.0f, 12.0f);

    proj = proj*view*model;

    glStencilFunc(GL_NEVER, 0x0, 0xFF);//第一次绘制，通通不通过模版测试。
    glStencilOp(GL_INCR, GL_INCR, GL_INCR);//第一次绘制的像素的模版值 0+1 = 1

    {
        glm::vec4 pos[] =
        {
            glm::vec4(-2.0f, -2.0f, 1.5f, 1.0f),
            glm::vec4(2.0f, -2.0f, 1.5f, 1.0f),
            glm::vec4(0.0f, 2.0f, 1.5f, 1.0f), //这个点已经在远裁剪面之外了，所以被裁剪掉了。
        };

        glm::vec4 color[] =
        {
            glm::vec4(1, 0, 0, 1),
            glm::vec4(1, 0, 0, 1),
            glm::vec4(1, 0, 0, 1),
        };

        glUniformMatrix4fv(mUMVPMatrixHandle, 1, false, &proj[0][0]);

        glVertexAttribPointer(mAPositionHandle, 4, GL_FLOAT, false, sizeof(glm::vec4), pos);
        glVertexAttribPointer(mAColorHandle, 4, GL_FLOAT, false, sizeof(glm::vec4), color);

        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    {
        glStencilFunc(GL_EQUAL, 0x1, 0xFF);//等于1 通过测试 ,就是上次绘制的图 的范围 才通过测试。
        glStencilFunc(GL_NOTEQUAL, 0x1, 0xFF);//不等于1 通过测试 就是除了上次绘制的图案之外的像素通过测试，所以上次绘制的像素之外的像素才可以进行第二幅图的绘制。
        //glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);//没有通过测试的，保留原来的，也就是保留上一次的值。

        glm::vec4 pos[] =
        {
            glm::vec4(0.0f, -2.0f, 1.5f, 1.0f),
            glm::vec4(4.0f, -2.0f, 1.5f, 1.0f),
            glm::vec4(2.0f, 2.0f, 1.5f, 1.0f),
        };

        glm::vec4 color[] =
        {
            glm::vec4(1, 1, 0, 1),
            glm::vec4(1, 1, 0, 1),
            glm::vec4(1, 1, 0, 1),
        };

        glUniformMatrix4fv(mUMVPMatrixHandle, 1, false, &proj[0][0]);

        glVertexAttribPointer(mAPositionHandle, 4, GL_FLOAT, false, sizeof(glm::vec4), pos);
        glVertexAttribPointer(mAColorHandle, 4, GL_FLOAT, false, sizeof(glm::vec4), color);
        glEnableVertexAttribArray(mAPositionHandle);
        glEnableVertexAttribArray(mAColorHandle);

        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

}
