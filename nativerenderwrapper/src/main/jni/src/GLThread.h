#ifndef __H_GLTHREAD_H__
#define __H_GLTHREAD_H__
#include <pthread.h>
#include <android/native_window.h>
#include <EGL/egl.h>
#include <GLES/gl.h>
#include "GLRenderer.h"
#include "esUtils.h"
// 一个线程类,用于调用Renderer,处理Renderer运行状态
// 类比GLThread线程类
class GLThread
{
public:
    enum RenderEvent {
        RE_NONE,
        RE_SURFACE_CREATED,
        RE_SURFACE_CHANGED,
        RE_DRAW_FRAME,
        RE_EXIT
    };

    enum RenderEvent mEnumRenderEvent;
    pthread_t  mThread;
    pthread_mutex_t mMutex;
    pthread_cond_t mCondVar;

    ANativeWindow *mWindow;
    EGLint mWidth;
    EGLint mHeight;

    EGLDisplay mDisplay;
    EGLSurface mSurface;
    EGLContext mContext;

    GLRenderer mRenderer;
public:
    GLThread(void* pixels);
    ~GLThread();
    void onRenderThreadRun();

    void start();
    void stop();

    void requestInitEGL(ANativeWindow * pWindow);
    void requestRenderFrame();
    void requestDestroy();

    static void *startRenderThread(void * pVoid);

    void initEGL();
    void terminateDisplay();

    bool mISRenderering;

};
#endif //__H_GLTHREAD_H__