#include <EGL/egl.h>
#include <GLES/gl.h>
#include "GLThread.h"
#include "esUtils.h"
#include "GLRenderer.h"
/*
* 实现
*/
GLThread::GLThread(void* pixels)
{
    pthread_mutex_init(&mMutex, NULL);
    pthread_cond_init(&mCondVar, NULL);

    mDisplay = EGL_NO_DISPLAY;
    mSurface = EGL_NO_SURFACE;
    mContext = EGL_NO_CONTEXT;

}
GLThread::~GLThread()
{
    pthread_mutex_destroy(&mMutex);
    pthread_cond_destroy(&mCondVar);
}
/*
* 类似一个状态机
*/
void GLThread::onRenderThreadRun()
{
    mISRenderering = true;
    while(mISRenderering) {
        pthread_mutex_lock(&mMutex);
        // 每完成一个事件就wait在这里直到有其他事件唤醒
        pthread_cond_wait(&mCondVar, &mMutex);

        LOGI(" this mEnumRenderEvent is %d", mEnumRenderEvent);
        switch (mEnumRenderEvent) {
            case RE_SURFACE_CHANGED:
                LOGI(" case RE_SURFACE_CHANGED");
                mEnumRenderEvent = RE_NONE;
                pthread_mutex_unlock(&mMutex);
                initEGL();
                mRenderer.nativeSurfaceCreated();
                mRenderer.nativeSurfaceChanged(mWidth, mHeight);
                break;
            case RE_DRAW_FRAME:
                mEnumRenderEvent = RE_NONE;
                pthread_mutex_unlock(&mMutex);
                // draw
                mRenderer.nativeDraw();
                eglSwapBuffers(mDisplay, mSurface);
                break;
            case RE_EXIT:
                mEnumRenderEvent = RE_NONE;
                pthread_mutex_unlock(&mMutex);
                terminateDisplay();
                mISRenderering = false;
                LOGI("status machine RE_EXIT");
                break;
            default:
                mEnumRenderEvent = RE_NONE;
                pthread_mutex_unlock(&mMutex);
        }

    }
}

void GLThread::start()
{
    pthread_create(&mThread, NULL, startRenderThread, this);
}

void *GLThread::startRenderThread(void * pVoid) {
    GLThread * glthread = (GLThread*) pVoid;
    glthread->onRenderThreadRun();
}

void GLThread::stop()
{
}

void GLThread::initEGL()
{
    const EGLint attribs[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_NONE
    };
    EGLint width, height, format;
    EGLint numConfigs;
    EGLConfig config;
    EGLSurface surface;
    EGLContext context;

    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    eglInitialize(display, 0, 0);

    eglChooseConfig(display, attribs, &config, 1, &numConfigs);

    surface = eglCreateWindowSurface(display, config, mWindow, NULL);
    EGLint attrs[]= {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
    context = eglCreateContext(display, config, NULL, attrs);

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
        return ;
    }

    eglQuerySurface(display, surface, EGL_WIDTH, &width);
    eglQuerySurface(display, surface, EGL_HEIGHT, &height);

    mDisplay = display;
    mSurface = surface;
    mContext = context;
    mWidth = width;
    mHeight = height;
    LOGI("width:%d, height:%d", mWidth, mHeight);

}

void GLThread::terminateDisplay() {
    if (mDisplay != EGL_NO_DISPLAY) {
        eglMakeCurrent(mDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (mContext != EGL_NO_CONTEXT) {
            eglDestroyContext(mDisplay, mContext);
        }
        if (mSurface != EGL_NO_SURFACE) {
            eglDestroySurface(mDisplay, mSurface);
        }
        eglTerminate(mDisplay);
    }

    mDisplay = EGL_NO_DISPLAY;
    mSurface = EGL_NO_SURFACE;
    mContext = EGL_NO_CONTEXT;
}

void GLThread::requestInitEGL(ANativeWindow * pWindow)
{
    pthread_mutex_lock(&mMutex);
    mWindow = pWindow;
    mEnumRenderEvent = RE_SURFACE_CHANGED;
    pthread_mutex_unlock(&mMutex);
    pthread_cond_signal(&mCondVar);
}

void GLThread::requestRenderFrame()
{
    pthread_mutex_lock(&mMutex);
    mEnumRenderEvent = RE_DRAW_FRAME;
    pthread_mutex_unlock(&mMutex);
    pthread_cond_signal(&mCondVar);
}

void GLThread::requestDestroy()
{
    pthread_mutex_lock(&mMutex);
    mEnumRenderEvent = RE_EXIT;
    pthread_mutex_unlock(&mMutex);
    pthread_cond_signal(&mCondVar);
    LOGI("requestDestroy");
}




