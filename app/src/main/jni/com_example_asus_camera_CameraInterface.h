/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_example_asus_camera_CameraInterface */

#ifndef _Included_com_example_asus_camera_CameraInterface
#define _Included_com_example_asus_camera_CameraInterface
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_example_asus_camera_CameraInterface
 * Method:    ImgFun
 * Signature: ([BII)[I
 */
JNIEXPORT jintArray JNICALL Java_com_example_asus_camera_CameraInterface_ImgFun
  (JNIEnv *, jobject, jbyteArray, jint, jint);

/*
 * Class:     com_example_asus_camera_CameraInterface
 * Method:    ImgSave
 * Signature: ([III)[I
 */
JNIEXPORT jintArray JNICALL Java_com_example_asus_camera_CameraInterface_ImgSave
  (JNIEnv *, jobject, jintArray, jint, jint);

/*
 * Class:     com_example_asus_camera_CameraInterface
 * Method:    ImgSaveSketch
 * Signature: ([III)[I
 */
JNIEXPORT jintArray JNICALL Java_com_example_asus_camera_CameraInterface_ImgSaveSketch
  (JNIEnv *, jobject, jintArray, jint, jint);

/*
 * Class:     com_example_asus_camera_CameraInterface
 * Method:    ImgFunVoid
 * Signature: ([B[BII)V
 */
JNIEXPORT void JNICALL Java_com_example_asus_camera_CameraInterface_ImgFunVoid
  (JNIEnv *, jobject, jbyteArray, jintArray, jint, jint);

#ifdef __cplusplus
}
#endif
#endif