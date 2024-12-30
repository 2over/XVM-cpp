//
// Created by xiehao on 2024/12/12.
//
#include "../../include/jni/com_cover_jvm_jdk_classes_Threads.h"
#include "../../share/vm/gc_implementation/shared/VM_GenCollectForAllocation.h"
#include "../../share/vm/runtime/VMThread.h"
#include "../../share/vm/memory/Universe.h"
#include "../../share/vm/memory/genCollectedHeap.h"
#include "../../share/vm/classfile/SystemDictionary.h"

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
    INFO_PRINT("Hello \n");
    g_env = env;
    env->GetJavaVM(&g_jvm);
    INFO_PRINT("GetJavaVM Finish\n");
    init_globals();

    SystemDictionary::initialize();
//    Hashmap::initialize();
}

/*
 * Class:     com_cover_jvm_jdk_classes_Threads
 * Method:    gc
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_cover_jvm_jdk_classes_Threads_gc
        (JNIEnv *env, jclass clazz) {

    VM_GenCollectForAllocation op(16);
    VMThread::execute(&op);

}

/*
 * Class:     com_cover_jvm_jdk_classes_Threads
 * Method:    fullGc
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_cover_jvm_jdk_classes_Threads_fullGc
        (JNIEnv *, jclass) {

}

// ====

void init_globals() {
    INFO_PRINT("init_globals\n");
    universe_init();
    universe_post_init();
}

void universe_init() {
    INFO_PRINT("\t universe_init\n");
    Universe::initialize_heap();
}

bool universe_post_init() {
    GenCollectedHeap *heap = (GenCollectedHeap *) Universe::heap();
    heap->post_initialize();

    return true;
}