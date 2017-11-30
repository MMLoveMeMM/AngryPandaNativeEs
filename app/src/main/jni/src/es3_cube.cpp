#include "es3_cube.h"
#include "es3_matrix.h"
const char VERTEX_SHADER[] =
                "#version 300 es\n"
                "layout(location = " STRV(POSITION_IND) ") in vec4 a_position;\n"
                "layout(location = " STRV(COLOR_IND) ") in vec4 a_color;\n"
                "layout(location = " STRV(MVP_IND) ") in mat4 a_mvpMatrix;\n"
                "out vec4 v_color;\n"
                "void main()\n"
                "{\n"
                "   v_color = a_color;\n"
                "   gl_Position = a_mvpMatrix * a_position;\n"
                "}\n";
const char FRAGMENT_SHADER[] =
                "#version 300 es\n"
                "precision mediump float;\n"
                "in vec4 v_color;\n"
                "layout(location = 0) out vec4 outColor;\n"
                "void main()\n"
                "{\n"
                "  outColor = v_color;\n"
                "}\n";

GLfloat VERTEX_POS[VERTEX_NUM] =
        {
                -0.5f, -0.5f, -0.5f,//0
                0.5f, -0.5f, 0.5f,//2
                -0.5f, -0.5f, 0.5f,//1
                -0.5f, -0.5f, -0.5f,//0
                0.5f, -0.5f, -0.5f,//3
                0.5f, -0.5f, 0.5f,//2
                -0.5f, 0.5f, -0.5f,//4
                -0.5f, 0.5f, 0.5f,//5
                0.5f, 0.5f, 0.5f,//6
                -0.5f, 0.5f, -0.5f,//4
                0.5f, 0.5f, 0.5f,//6
                0.5f, 0.5f, -0.5f,//7
                -0.5f, -0.5f, -0.5f,//0
                -0.5f, 0.5f, -0.5f,//4
                0.5f, 0.5f, -0.5f,//7
                -0.5f, -0.5f, -0.5f,//0
                0.5f, 0.5f, -0.5f,//7
                0.5f, -0.5f, -0.5f,//3
                -0.5f, -0.5f, 0.5f,//1
                0.5f, -0.5f, 0.5f,//2
                0.5f, 0.5f, 0.5f,//6
                -0.5f, -0.5f, 0.5f,//1
                0.5f, 0.5f, 0.5f,//6
                -0.5f, 0.5f, 0.5f,//5
                -0.5f, -0.5f, -0.5f,//0
                -0.5f, -0.5f, 0.5f,//1
                -0.5f, 0.5f, 0.5f,//5
                -0.5f, -0.5f, -0.5f,//0
                -0.5f, 0.5f, 0.5f,//5
                -0.5f, 0.5f, -0.5f,//4
                0.5f, -0.5f, -0.5f,//3
                0.5f, 0.5f, -0.5f,//7
                0.5f, 0.5f, 0.5f,//6
                0.5f, -0.5f, -0.5f,//3
                0.5f, 0.5f, 0.5f,//6
                0.5f, -0.5f, 0.5f//2
        };
const GLfloat cubeColor[] =
        {
                1.0f, 0.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                1.0f, 1.0f, 0.0f, 0.0f,
                1.0f, 1.0f, 0.0f, 0.0f,
                1.0f, 1.0f, 0.0f, 0.0f,
                1.0f, 1.0f, 0.0f, 0.0f,
                1.0f, 1.0f, 0.0f, 0.0f,
                1.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 1.0f, 0.0f,
                1.0f, 0.0f, 1.0f, 0.0f,
                1.0f, 0.0f, 1.0f, 0.0f,
                1.0f, 0.0f, 1.0f, 0.0f,
                1.0f, 0.0f, 1.0f, 0.0f,
                1.0f, 0.0f, 1.0f, 0.0f,
                1.0f, 0.0f, 1.0f, 0.0f
        };

void es3cube::update(float deltaTime) {
    Matrix *matrixBuf;
    Matrix perspective;
    es3matrix::matrixLoadIdentity(&perspective);
    GLfloat frustumW, frustumH;
    frustumH = tanf(float(60.0f / 360.0f * PI)) * 1.5f;
    frustumW = frustumH * aspect;
    es3matrix::frustum(&perspective, frustumW, frustumH, 1.0f, 20.0f);
    glBindBuffer(GL_ARRAY_BUFFER, mvpVBO);
    matrixBuf = (Matrix *) glMapBufferRange(GL_ARRAY_BUFFER, 0, sizeof(Matrix),
                                            GL_MAP_WRITE_BIT);
    Matrix modelview;
    es3matrix::matrixLoadIdentity(&modelview);
    es3matrix::translate(&modelview, 0, 0, -2.0f);
    angle += (deltaTime * 40.0f);
    if (angle >= 360.0f) {
        angle -= 360.0f;
    }
    es3matrix::rotate(&modelview, angle, 1.0, 0.0, 1.0);
    es3matrix::matrixMultiply(&matrixBuf[0], &modelview, &perspective);
    glUnmapBuffer(GL_ARRAY_BUFFER);
}

bool es3cube::init()
{
    /*
    * 加载编译glsl
    */
    program = es3shader::createProgram(VERTEX_SHADER, FRAGMENT_SHADER);
    if (!program)
    {
        return false;
    }

    // 函数参照readme.txt
    glGenBuffers(1, &positionVBO); // 产生缓存区
    glBindBuffer(GL_ARRAY_BUFFER, positionVBO); // 通过上面的索引句柄绑定缓冲区
    // 拷贝数据到缓存区,GL_STATIC_DRAW :数据不会或几乎不会改变
    glBufferData(GL_ARRAY_BUFFER, VERTEX_NUM * sizeof(GLfloat), VERTEX_POS, GL_STATIC_DRAW);
    glGenBuffers(1, &colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glBufferData(GL_ARRAY_BUFFER, INDICES_NUM * 4 * sizeof(GLfloat), cubeColor, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glVertexAttribPointer(COLOR_IND, 4, GL_FLOAT,
                          GL_FALSE, 0, (const void *) NULL);
    glEnableVertexAttribArray(COLOR_IND);
    angle = float(drand48() * 360.0f);
    glGenBuffers(1, &mvpVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mvpVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Matrix), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
    glVertexAttribPointer(POSITION_IND, 3, GL_FLOAT,
                          GL_FALSE, 3 * sizeof(GLfloat), (const void *) NULL);
    glEnableVertexAttribArray(POSITION_IND);
    glBindBuffer(GL_ARRAY_BUFFER, mvpVBO);
    glVertexAttribPointer(MVP_IND + 0, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix),
                          (const void *) NULL);
    glVertexAttribPointer(MVP_IND + 1, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix),
                          (const void *) (sizeof(GLfloat) * 4));
    glVertexAttribPointer(MVP_IND + 2, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix),
                          (const void *) (sizeof(GLfloat) * 8));
    glVertexAttribPointer(MVP_IND + 3, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix),
                          (const void *) (sizeof(GLfloat) * 12));
    glEnableVertexAttribArray(MVP_IND + 0);
    glEnableVertexAttribArray(MVP_IND + 1);
    glEnableVertexAttribArray(MVP_IND + 2);
    glEnableVertexAttribArray(MVP_IND + 3);
    glVertexAttribDivisor(MVP_IND + 0, 1);
    glVertexAttribDivisor(MVP_IND + 1, 1);
    glVertexAttribDivisor(MVP_IND + 2, 1);
    glVertexAttribDivisor(MVP_IND + 3, 1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesIBO);
    glUseProgram(program);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    return true;
}

void es3cube::resize(int width,int height)
{
    aspect = (GLfloat) width / (GLfloat) height;
    glViewport(0, 0, width, height);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void es3cube::render()
{
    timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    auto nowNs = now.tv_sec * 1000000000ull + now.tv_nsec;
    if (lastFrameNs > 0) {
        float dt = float(nowNs - lastFrameNs) * 0.000000001f;
        update(dt);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    lastFrameNs = nowNs;
}

void es3cube::destroy()
{
    /*
    * 清除产生的缓存区
    */
    glDeleteBuffers(1, &positionVBO);
    glDeleteBuffers(1, &colorVBO);
    glDeleteBuffers(1, &mvpVBO);
    glDeleteBuffers(1, &indicesIBO);
    glDeleteProgram(program);
}