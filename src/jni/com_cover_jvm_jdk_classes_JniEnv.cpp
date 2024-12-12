//
// Created by xiehao on 2024/12/12.
//
#include "../../include/jni/com_cover_jvm_jdk_classes_JniEnv.h"
#include "../../include/common.h"
#include "../"


/*
 * Class:     com_cover_jvm_jdk_classes_JniEnv
 * Method:    getMethodID
 * Signature: (Lcom/cover/jvm/jdk/classes/Handle;Ljava/lang/String;Ljava/lang/String;)Lcom/cover/jvm/jdk/classes/Handle;
 */
JNIEXPORT jobject JNICALL Java_com_cover_jvm_jdk_classes_JniEnv_getMethodID
        (JNIEnv *env, jclass clazz, jobject klass_handle, jstring method_name, jstring descriptor_name) {
    Inst
}

/*
 * Class:     com_cover_jvm_jdk_classes_JniEnv
 * Method:    CallStaticVoidMethod
 * Signature: (Lcom/cover/jvm/jdk/classes/Handle;Lcom/cover/jvm/jdk/classes/Handle;)V
 */
JNIEXPORT void JNICALL Java_com_cover_jvm_jdk_classes_JniEnv_CallStaticVoidMethod
        (JNIEnv *, jclass, jobject, jobject);
