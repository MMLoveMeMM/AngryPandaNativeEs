 #ifndef __H_RENDERER_H__
 #define __H_RENDERER_H__
 #ifdef __cplusplus
 extern "C"{
 #endif

/*
模仿GLSurfaceView.java里面的Renderer接口类
*/
#include <EGL/egl.h>
#include <GLES/gl.h>
class Renderer
{
public :
    Renderer();
    virtual ~Renderer();

    virtual void nativeSurfaceCreated(){};

    virtual void nativeSurfaceChanged(EGLint width, EGLint height){};

    virtual void nativeDraw(){};
};
#ifdef __cplusplus
}
#endif
#endif //__H_RENDERER_H__