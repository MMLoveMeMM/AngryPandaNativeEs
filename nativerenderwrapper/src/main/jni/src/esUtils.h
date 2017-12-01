#ifndef __H_ES_UTILS_H__
#define __H_ES_UTILS_H__

#ifdef __cplusplus
extern "C"{
#endif
#include <GLES2/gl2.h>
#include <android/log.h>
#define LOGI(level, ...) __android_log_print(ANDROID_LOG_INFO, "NATIVE_LOG", __VA_ARGS__)
class GLUtil {
public:
    static int compileShader(int type, const char* shaderCode);
    static int createProgram(const char * vertexShaderCode, const char * fragmentShaderCode);
};

#ifdef __cplusplus
}
#endif

#endif //__H_ES_UTILS_H__