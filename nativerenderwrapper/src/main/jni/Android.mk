LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := nativerenderer

LOCAL_SRC_FILES :=./glm/detail/*.* ./glm/gtc/*.* ./glm/gtx/*.* ./glm/simd/*.* ./glm/*.*
LOCAL_SRC_FILES += src/esUtils.cpp \
                    src/utils/esMatrix.cpp \
                    src/utils/esShader.cpp \
                    src/shape/Triangle.cpp \
                    src/shape/TriangleBuff.cpp \
                    src/shape/TriangleTexture.cpp \
                    src/GLThread.cpp \
                    src/Renderer.cpp \
                    src/GLRenderer.cpp \
                    NativeSurfaceView.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/ \
                    $(LOCAL_PATH)/src \
                    $(LOCAL_PATH)/src/utils \
                    $(LOCAL_PATH)/src/shape

LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv3 -ljnigraphics
LOCAL_LDLIBS += -latomic
#LOCAL_LDLIBS := -lGLESv2 -llog -lEGL -landroid -ljnigraphics

include $(BUILD_SHARED_LIBRARY)