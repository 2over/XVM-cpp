//
// Created by xiehao on 2024/12/25.
//
#include "../../include/jni/com_cover_jvm_jdk_classes_sun_misc_Unsafe.h"
#include "../../include/common.h"
#include "../../share/vm/oops/InstanceKlass.h"

/*
 * Class:     com_cover_jvm_jdk_classes_sun_misc_Unsafe
 * Method:    allocateMemory
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_cover_jvm_jdk_classes_sun_misc_Unsafe_allocateMemory
        (JNIEnv *env, jclass obj, jlong size) {
    INFO_PRINT("hello\n");
    return 0;

}

/*
 * Class:     com_cover_jvm_jdk_classes_sun_misc_Unsafe
 * Method:    allocateObject
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_cover_jvm_jdk_classes_sun_misc_Unsafe_allocateObject
        (JNIEnv *env, jclass clazz) {
    InstanceKlass* klass = new InstanceKlass;

    instanceOop i = klass->allocate_instance(16);
    return (jlong)i;
}

/*
 * Class:     com_cover_jvm_jdk_classes_sun_misc_Unsafe
 * Method:    initMemoryModel
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_cover_jvm_jdk_classes_sun_misc_Unsafe_initMemoryModel
(JNIEnv *env, jclass clazz) {

}