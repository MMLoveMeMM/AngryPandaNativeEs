#include "esShader.h"

GLShader::GLShader()
{
}
GLShader::~GLShader()
{
}
int GLShader::compileShader(int type, const char * shaderCode)
{

    int shader = glCreateShader(type);
    if (shader == 0) {

    }
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);
    GLint compileStatus = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
    if (!compileStatus) {
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

int GLShader::createProgram(const char *vertexShaderCode, const char *fragmentShaderCode)
{
    GLint program = glCreateProgram();
    if (0 == program) {
        return 0;
    }

    int vertexShaderID = compileShader(GL_VERTEX_SHADER, vertexShaderCode);
    int fragmentShaderID = compileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);

    glAttachShader(program, vertexShaderID);
    glAttachShader(program, fragmentShaderID);
    glLinkProgram(program);
    GLint linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if (0 == linkStatus) {
        glDeleteProgram(program);
        return 0;
    }
    return program;

}