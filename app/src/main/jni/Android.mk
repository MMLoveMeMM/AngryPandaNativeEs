LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := nativeses

LOCAL_SRC_FILES :=./glm/detail/*.* ./glm/gtc/*.* ./glm/gtx/*.* ./glm/simd/*.* ./glm/*.*
LOCAL_SRC_FILES += src/es3_triangleex.cpp \
                    src/es3_shader.cpp \
                    src/es3_rect.cpp \
                    RectRenderer.cpp \
                    src/es3_cube.cpp \
                    src/es3_matrix.cpp \
                    CubeRenderer.cpp \

LOCAL_C_INCLUDES := ./ \
                    src/es3_rect.h \
                    src/es3_shader.h \
                    src/es3_cube.h \
                    ./src \
                    src/

LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv3
LOCAL_LDLIBS += -latomic

include $(BUILD_SHARED_LIBRARY)