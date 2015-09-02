LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

OPENCV_CAMERA_MODULES:=off
OPENCV_INSTALL_MODULES:=on
OPENCV_LIB_TYPE:=STATIC
include G:\OpenCV-android-sdk\sdk\native\jni\OpenCV.mk


LOCAL_LDLIBS     += -lm -llog

LOCAL_MODULE     := ImgFun

LOCAL_SRC_FILES  := ImgFun.cpp


include $(BUILD_SHARED_LIBRARY)
