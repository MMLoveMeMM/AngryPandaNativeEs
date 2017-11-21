#include "es3_shader.h"
#include "es3_rect.h"
es3rect::es3rect() : mLastFrameNs(0),
                     mProgram(0),
                     mVBState(0)
{
    memset(mScale, 0, sizeof(mScale));
    for (int i = 0; i < VB_COUNT; i++)
    {
        mVB[i] = 0;
    }
}

es3rect::~es3rect()
{
    glDeleteVertexArrays(1, &mVBState);
    glDeleteBuffers(VB_COUNT, mVB);
    glDeleteProgram(mProgram);
}

bool es3rect::init()
{
    mProgram = es3shader::createProgram(VERTEX_SHADER, FRAGMENT_SHADER);
    if (!mProgram)
    {
        return false;
    }

    glGenBuffers(VB_COUNT, mVB);
    glBindBuffer(GL_ARRAY_BUFFER, mVB[VB_INSTANCE]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QUAD), &QUAD[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mVB[VB_SCALEROT]);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(float), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mVB[VB_OFFSET]);
    glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(float), NULL, GL_STATIC_DRAW);
    glGenVertexArrays(1, &mVBState);
    glBindVertexArray(mVBState);
    glBindBuffer(GL_ARRAY_BUFFER, mVB[VB_INSTANCE]);
    glVertexAttribPointer(POS_ATTRIB, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (const GLvoid *) offsetof(Vertex, pos));
    glVertexAttribPointer(COLOR_ATTRIB, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex),
                          (const GLvoid *) offsetof(Vertex, rgba));
    glEnableVertexAttribArray(POS_ATTRIB);
    glEnableVertexAttribArray(COLOR_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER, mVB[VB_SCALEROT]);
    glVertexAttribPointer(SCALEROT_ATTRIB, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glEnableVertexAttribArray(SCALEROT_ATTRIB);
    glVertexAttribDivisor(SCALEROT_ATTRIB, 1);
    glBindBuffer(GL_ARRAY_BUFFER, mVB[VB_OFFSET]);
    glVertexAttribPointer(OFFSET_ATTRIB, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(OFFSET_ATTRIB);
    glVertexAttribDivisor(OFFSET_ATTRIB, 1);
    return true;
}
void es3rect::resize(int w, int h)
{
    calcSceneParams(w, h);
    mAngles = float(drand48() * TWO_PI);
    mAngularVelocity = float(MAX_ROT_SPEED * (2.0 * drand48() - 1.0));
    mLastFrameNs = 0;
    glViewport(0, 0, w, h);
}
void es3rect::render()
{
    step();
    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
    es3shader::checkGlError("Renderer::render");
}

float *es3rect::mapTransformBuf()
{
    glBindBuffer(GL_ARRAY_BUFFER, mVB[VB_SCALEROT]);
        return (float *) glMapBufferRange(GL_ARRAY_BUFFER,
                                          0, 4 * sizeof(float),
                                          GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
}
void es3rect::unmapTransformBuf()
{
    glUnmapBuffer(GL_ARRAY_BUFFER);
}
void es3rect::draw()
{
    glUseProgram(mProgram);
    glBindVertexArray(mVBState);
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, 2);
}
void es3rect::calcSceneParams(int w, int h)
{
    const float CELL_SIZE = 0.5f;
    const float scene2clip[2] = {1.0f, fmaxf(w, h) / fminf(w, h)};
    int major = w >= h ? 0 : 1;
    int minor = w >= h ? 1 : 0;
    mScale[major] = CELL_SIZE * scene2clip[0];
    mScale[minor] = CELL_SIZE * scene2clip[1];
}
void es3rect::step()
{
    timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    auto nowNs = now.tv_sec * 1000000000ull + now.tv_nsec;
    if (mLastFrameNs > 0) {
        float dt = float(nowNs - mLastFrameNs) * 0.000000001f;
        mAngles += mAngularVelocity * dt;
        if (mAngles >= TWO_PI) {
            mAngles -= TWO_PI;
        } else if (mAngles <= -TWO_PI) {
            mAngles += TWO_PI;
        }
        float *transforms = mapTransformBuf();
        float s = sinf(mAngles);
        float c = cosf(mAngles);
        transforms[0] = c * mScale[0];
        transforms[1] = s * mScale[1];
        transforms[2] = -s * mScale[0];
        transforms[3] = c * mScale[1];
    }
    unmapTransformBuf();
    mLastFrameNs = nowNs;
}
