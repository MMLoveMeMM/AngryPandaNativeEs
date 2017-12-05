#ifndef __H_ES_SHADER_H__
#define __H_ES_SHADER_H__
#ifdef __cplusplus
extern "C"{
#endif
#include <GLES2/gl2.h>
class GLShader
{
public:
    GLShader();
    ~GLShader();

    static int createProgram(const char * vertexShaderCode, const char * fragmentShaderCode);

private:
    static int compileShader(int type, const char* shaderCode);
};

#ifdef __cplusplus
}
#endif

#endif //__H_ES_SHADER_H__
