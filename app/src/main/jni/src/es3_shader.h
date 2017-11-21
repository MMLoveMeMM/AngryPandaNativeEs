#ifndef __H_ES3_SHADER_H__
#define GLES_ESUTIL_H
#include <GLES3/gl3.h>
#include <android/log.h>
#include <jni.h>
#ifndef LOG_TAG
#define LOG_TAG "ES_LIB"
#endif
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#include <stdlib.h>
class es3shader
{
public:
    es3shader(){};
    ~es3shader(){};
public:
    //检查glsl脚本编译等是否错误
    static bool checkGlError(const char* funcName);
    //获取并编译着色器对象
    static GLuint createShader(GLenum shaderType, const char* src);
    //使用着色器生成着色器程序对象
    static GLuint createProgram(const char* vtxSrc, const char* fragSrc);
};
#endif //__H_ES3_SHADER_H__