#include <android/native_window_jni.h>
#include "com_panda_org_nativerenderwrapper_NativeSurfaceView.h"
#include "src/GLThread.h"
ANativeWindow * mWindow;
GLThread * mGLThread;
/*
 * Class:     com_panda_org_nativerenderwrapper_NativeSurfaceView
 * Method:    nativeSurfaceChanged
 * Signature: (Landroid/view/Surface;)V
 */
JNIEXPORT void JNICALL Java_com_panda_org_nativerenderwrapper_NativeSurfaceView_nativeSurfaceChanged
  (JNIEnv *env, jclass thiz, jobject surface)
  {
    mWindow = ANativeWindow_fromSurface(env, surface);
    // surfacechange时 发送SurfaceChanged消息，此时创建egl环境的消息
    mGLThread->requestInitEGL(mWindow);
  }

/*
 * Class:     com_panda_org_nativerenderwrapper_NativeSurfaceView
 * Method:    nativeSurfaceDestroyed
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_panda_org_nativerenderwrapper_NativeSurfaceView_nativeSurfaceDestroyed
  (JNIEnv *env, jclass thiz)
  {
    mGLThread->requestDestroy();
    ANativeWindow_release(mWindow);
    delete mGLThread;
  }

/*
 * Class:     com_panda_org_nativerenderwrapper_NativeSurfaceView
 * Method:    nativeStartRender
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_panda_org_nativerenderwrapper_NativeSurfaceView_nativeStartRender
  (JNIEnv *env, jclass thiz)
  {
    mGLThread = new GLThread();
    mGLThread->start();
  }

/*
 * Class:     com_panda_org_nativerenderwrapper_NativeSurfaceView
 * Method:    nativeRequestRender
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_panda_org_nativerenderwrapper_NativeSurfaceView_nativeRequestRender
  (JNIEnv *env, jclass thiz)
  {
    mGLThread->requestRenderFrame();
  }