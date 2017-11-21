#ifndef __H_ES3_RECT_H__
#define __H_ES3_RECT_H__
#include <GLES3/gl3.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "es3_utils.h"

static const char VERTEX_SHADER[] =
        "#version 300 es\n"
                "layout(location = " STRV(POS_ATTRIB) ") in vec2 pos;\n"
                "layout(location=" STRV(COLOR_ATTRIB) ") in vec4 color;\n"
                "layout(location=" STRV(SCALEROT_ATTRIB) ") in vec4 scaleRot;\n"
                "layout(location=" STRV(OFFSET_ATTRIB) ") in vec2 offset;\n"
                "out vec4 vColor;\n"
                "void main() {\n"
                "    mat2 sr = mat2(scaleRot.xy, scaleRot.zw);\n"
                "    gl_Position = vec4(sr*pos + offset, 0.0, 1.0);\n"
                "    vColor = color;\n"
                "}\n";
static const char FRAGMENT_SHADER[] =
        "#version 300 es\n"
                "precision mediump float;\n"
                "in vec4 vColor;\n"
                "out vec4 outColor;\n"
                "void main() {\n"
                "    outColor = vColor;\n"
                "}\n";
struct Vertex {
    GLfloat pos[2];
    GLubyte rgba[4];
};
const Vertex QUAD[4] = {
        {{-0.7f, -0.7f}, {0x00, 0xFF, 0x00}},
        {{0.7f,  -0.7f}, {0x00, 0x00, 0xFF}},
        {{-0.7f, 0.7f},  {0xFF, 0x00, 0x00}},
        {{0.7f,  0.7f},  {0xFF, 0xFF, 0xFF}},
};

class es3rect
{
public:
    es3rect();
    ~es3rect();

public:
    bool init();
    void resize(int w, int h);
    void render();

private:
    enum {
        VB_INSTANCE, VB_SCALEROT, VB_OFFSET, VB_COUNT
    };
    float mScale[2];
    float mAngularVelocity;
    uint64_t mLastFrameNs;
    float mAngles;
    GLuint mProgram;
    GLuint mVB[VB_COUNT];
    GLuint mVBState;
    float *mapTransformBuf();
    void unmapTransformBuf();
    void draw();
    void calcSceneParams(int w, int h);
    void step();
};
#define mRectInstance (es3rect::getInstance())
#endif //__H_ES3_RECT_H__