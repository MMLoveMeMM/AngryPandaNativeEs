#include "com_panda_org_angrypandanativees_basic_rl_RectRenderer.h"
#include "src/es3_rect.h"

es3rect *createRenderer() {
    es3rect *renderer = new es3rect;
    if (!renderer->init()) {
        delete renderer;
        return NULL;
    }
    return renderer;
}
static es3rect *g_renderer = NULL;

/*
 * Class:     com_panda_org_angrypandanativees_basic_rl_RectRenderer
 * Method:    init
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_panda_org_angrypandanativees_basic_rl_RectRenderer_init
  (JNIEnv *env, jobject thiz)
  {
    /*
    * 做成了单实例,并且通过预定义初始化了
    */
    if (g_renderer) {
        delete g_renderer;
        g_renderer = NULL;
    }
    g_renderer = createRenderer();
    if (!g_renderer)
        return JNI_FALSE;
    return JNI_TRUE;
  }

/*
 * Class:     com_panda_org_angrypandanativees_basic_rl_RectRenderer
 * Method:    resize
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_com_panda_org_angrypandanativees_basic_rl_RectRenderer_resize
  (JNIEnv *env, jobject thiz, jint width, jint height)
  {
    if (g_renderer) {
      g_renderer->resize(width, height);
    }
  }

/*
 * Class:     com_panda_org_angrypandanativees_basic_rl_RectRenderer
 * Method:    step
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_panda_org_angrypandanativees_basic_rl_RectRenderer_step
  (JNIEnv *env, jobject thiz)
  {
    if (g_renderer) {
      g_renderer->render();
    }
  }

/*
 * Class:     com_panda_org_angrypandanativees_basic_rl_RectRenderer
 * Method:    destroy
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_panda_org_angrypandanativees_basic_rl_RectRenderer_destroy
  (JNIEnv *env, jobject thiz)
  {
    // nothing to do
    delete g_renderer;
    g_renderer = NULL;
  }







