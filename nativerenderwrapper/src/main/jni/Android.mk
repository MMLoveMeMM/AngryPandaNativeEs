LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := nativerenderer

LOCAL_SRC_FILES :=./glm/detail/*.* ./glm/gtc/*.* ./glm/gtx/*.* ./glm/simd/*.* ./glm/*.*
LOCAL_SRC_FILES += src/esUtils.cpp \
                    src/GLThread.cpp \
                    src/Renderer.cpp \
                    src/GLRenderer.cpp \
                    src/Triangle.cpp \
                    NativeSurfaceView.cpp \

LOCAL_C_INCLUDES := ./ \
                    ./src \

LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv3
LOCAL_LDLIBS += -latomic
#LOCAL_LDLIBS := -lGLESv2 -llog -lEGL -landroid

include $(BUILD_SHARED_LIBRARY)