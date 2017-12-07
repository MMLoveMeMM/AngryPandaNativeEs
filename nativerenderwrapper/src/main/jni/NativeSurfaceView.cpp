#include <android/native_window_jni.h>
#include <android/bitmap.h>
#include "com_panda_org_nativerenderwrapper_NativeSurfaceView.h"
#include "src/GLThread.h"
#include "NativeLog.h"
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
    LOGI("Java_com_panda_org_nativerenderwrapper_NativeSurfaceView_nativeSurfaceDestroyed END");
  }

/*
 * Class:     com_panda_org_nativerenderwrapper_NativeSurfaceView
 * Method:    nativeStartRender
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_panda_org_nativerenderwrapper_NativeSurfaceView_nativeStartRender
  (JNIEnv *env, jclass thiz)
  {
    mGLThread = new GLThread(NULL);
    mGLThread->start();
  }

/*
* Class:     com_panda_org_nativerenderwrapper_NativeSurfaceView
* Method:    nativeStartTextureRender
* Signature: (Landroid/graphics/Bitmap;)V
*/
JNIEXPORT void JNICALL Java_com_panda_org_nativerenderwrapper_NativeSurfaceView_nativeStartTextureRender
(JNIEnv *env, jclass clazz, jobject zBitmap)
{
    JNIEnv J = *env;
    if (zBitmap == NULL) {
        LOGE("bitmap is null\n");
        return;
    }

    // Get bitmap info
    AndroidBitmapInfo info;
    memset(&info, 0, sizeof(info));
    AndroidBitmap_getInfo(env, zBitmap, &info);
    // Check format, only RGB565 & RGBA are supported
    if (info.width <= 0 || info.height <= 0 ||
        (info.format != ANDROID_BITMAP_FORMAT_RGB_565 && info.format != ANDROID_BITMAP_FORMAT_RGBA_8888)) {
        LOGE("invalid bitmap\n");
        //J->ThrowNew(J->FindClass(env, "java/io/IOException"), "invalid bitmap");
        return;
    }

    // Lock the bitmap to get the buffer
    void * pixels = NULL; // pixels是需要获取的值
    int res = AndroidBitmap_lockPixels(env, zBitmap, &pixels);
    if (pixels == NULL) {
        LOGE("fail to lock bitmap: %d\n", res);
        //J->ThrowNew(J->FindClass(env, "java/io/IOException"), "fail to open bitmap");
        return;
    }

    mGLThread = new GLThread(pixels);
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