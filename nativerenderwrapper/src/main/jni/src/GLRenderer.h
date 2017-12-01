#ifndef __H_GL_RENDERER_H__
#define __H_GL_RENDERER_H__
#ifdef __cplusplus
extern "C"{
#endif

#include <EGL/egl.h>
#include <GLES/gl.h>
#include "Renderer.h"
class GLRenderer : public Renderer
{
public:
    void requestInitEGL(ANativeWindow * pWindow);
    void requestRenderFrame();
    void requestDestroy();

    virtual void nativeSurfaceCreated();

    virtual void nativeSurfaceChanged(EGLint width, EGLint height);

    virtual void nativeDraw();

};
#ifdef __cplusplus
}
#endif

#endif //__H_GL_RENDERER_H__