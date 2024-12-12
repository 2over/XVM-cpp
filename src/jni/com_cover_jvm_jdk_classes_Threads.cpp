//
// Created by xiehao on 2024/12/12.
//
#include "../../include/jni/com_cover_jvm_jdk_classes_Threads.h"



/*
 * Class:     com_cover_jvm_jdk_classes_Threads
 * Method:    createVM
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_cover_jvm_jdk_classes_Threads_createVM
        (JNIEnv *, jclass);

/*
 * Class:     com_cover_jvm_jdk_classes_Threads
 * Method:    gc
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_cover_jvm_jdk_classes_Threads_gc
        (JNIEnv *, jclass);

/*
 * Class:     com_cover_jvm_jdk_classes_Threads
 * Method:    fullGc
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_cover_jvm_jdk_classes_Threads_fullGc
        (JNIEnv *, jclass);