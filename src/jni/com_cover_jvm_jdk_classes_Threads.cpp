//
// Created by xiehao on 2024/12/12.
//
#include "../../include/jni/com_cover_jvm_jdk_classes_Threads.h"

JavaVM* g_jvm = NULL;
JNIEnv* g_env = NULL;

void universe_init();
bool universe_post_init();
void init_globals();


/*
 * Class:     com_cover_jvm_jdk_classes_Threads
 * Method:    createVM
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_cover_jvm_jdk_classes_Threads_createVM
        (JNIEnv *env, jclass clazz) {
    g_env = env;
    env->GetJavaVM(&g_jvm);
}

/*
 * Class:     com_cover_jvm_jdk_classes_Threads
 * Method:    gc
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_cover_jvm_jdk_classes_Threads_gc
        (JNIEnv *env, jclass clazz) {

    VM_GenCollectForAllocation op(16);

}

/*
 * Class:     com_cover_jvm_jdk_classes_Threads
 * Method:    fullGc
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_cover_jvm_jdk_classes_Threads_fullGc
        (JNIEnv *, jclass);