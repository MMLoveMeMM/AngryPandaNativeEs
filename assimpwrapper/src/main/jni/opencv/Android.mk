LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := opencv
LOCAL_SRC_FILES := ./libs/armeabi-v7a/libopencv_java3.so
include $(PREBUILT_SHARED_LIBRARY)