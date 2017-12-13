LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := assimp
LOCAL_SRC_FILES := ./libs/armeabi-v7a/libassimp.so
include $(PREBUILT_SHARED_LIBRARY)