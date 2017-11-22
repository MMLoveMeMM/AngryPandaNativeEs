#include "com_panda_org_angrypandanativees_basic_rl_CubeRenderer.h"
#include "src/es3_cube.h"
es3cube *createCubeRenderer() {
    es3cube *renderer = new es3cube;
    if (!renderer->init()) {
        delete renderer;
        return NULL;
    }
    return renderer;
}
static es3cube *g_cuberenderer = NULL;
/*
 * Class:     com_panda_org_angrypandanativees_basic_rl_CubeRenderer
 * Method:    init
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_panda_org_angrypandanativees_basic_rl_CubeRenderer_init
  (JNIEnv *env, jobject thiz)
  {
    if (g_cuberenderer) {
        delete g_cuberenderer;
        g_cuberenderer = NULL;
    }
    g_cuberenderer = createCubeRenderer();
    if (!g_cuberenderer)
        return JNI_FALSE;
    return JNI_TRUE;
  }

/*
 * Class:     com_panda_org_angrypandanativees_basic_rl_CubeRenderer
 * Method:    resize
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_com_panda_org_angrypandanativees_basic_rl_CubeRenderer_resize
  (JNIEnv *env, jobject thiz, jint width, jint height)
  {
    if (g_cuberenderer) {
        g_cuberenderer->resize(width, height);
    }
  }

/*
 * Class:     com_panda_org_angrypandanativees_basic_rl_CubeRenderer
 * Method:    render
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_panda_org_angrypandanativees_basic_rl_CubeRenderer_render
  (JNIEnv *env, jobject thiz)
  {
    if (g_cuberenderer) {
        g_cuberenderer->render();
    }
  }

/*
 * Class:     com_panda_org_angrypandanativees_basic_rl_CubeRenderer
 * Method:    destroy
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_panda_org_angrypandanativees_basic_rl_CubeRenderer_destroy
  (JNIEnv *env, jobject thiz)
  {
    if (g_cuberenderer) {
      g_cuberenderer->destroy();
    }
  }

