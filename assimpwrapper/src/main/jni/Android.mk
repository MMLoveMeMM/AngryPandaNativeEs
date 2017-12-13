LOCAL_PATH:= $(call my-dir)
MY_PATH := $(LOCAL_PATH)
include $(call all-subdir-makefiles)
LOCAL_PATH := $(TOP_LOCAL_PATH)
include $(CLEAR_VARS)
LOCAL_PATH := $(MY_PATH)

