//
// Created by xiehao on 2024/12/12.
//
#include "../../include/jni/com_cover_jvm_jdk_classes_JniEnv.h"
#include "../../include/common.h"
#include "../../include/jni/Handle.h"
#include "../../include/jni/JniTools.h"
#include "../../share/vm/oops/InstanceKlass.h"
#include "../../share/vm/prims/JavaNativeInterface.h"
#include "../../share/vm/runtime/JavaThread.h"
#include "../../share/vm/runtime/Threads.h"


/*
 * Class:     com_cover_jvm_jdk_classes_JniEnv
 * Method:    getMethodID
 * Signature: (Lcom/cover/jvm/jdk/classes/Handle;Ljava/lang/String;Ljava/lang/String;)Lcom/cover/jvm/jdk/classes/Handle;
 */
JNIEXPORT jobject JNICALL Java_com_cover_jvm_jdk_classes_JniEnv_getMethodID
        (JNIEnv *env, jclass clazz, jobject klass_handle, jstring method_name, jstring descriptor_name) {

    InstanceKlass *klass = static_cast<InstanceKlass *>(Handle::klass(env, klass_handle));

    vector<MethodInfo *> methods = klass->methods();
    string *name_str = JniTools::jstringToString(env, method_name, true);
    string *descriptor_str = JniTools::jstringToString(env, descriptor_name, true);

    MethodInfo *ret = NULL;

    for (int i = 0; i < methods.size(); i++) {
        MethodInfo *method = methods[i];
        if ((*name_str == method->name()) && (*descriptor_str == method->descriptor())) {
            ret = method;
        }
    }

    return Handle::methodToHandle(env, ret);
}

/*
 * Class:     com_cover_jvm_jdk_classes_JniEnv
 * Method:    CallStaticVoidMethod
 * Signature: (Lcom/cover/jvm/jdk/classes/Handle;Lcom/cover/jvm/jdk/classes/Handle;)V
 */
JNIEXPORT void JNICALL Java_com_cover_jvm_jdk_classes_JniEnv_CallStaticVoidMethod
        (JNIEnv *env, jclass clazz, jobject klass_handle, jobject method_handle) {

    InstanceKlass *klass = static_cast<InstanceKlass *>(Handle::klass(env, klass_handle));
    MethodInfo *method = Handle::method(env, method_handle);

    JavaThread *thread = new JavaThread(nullptr);
    Threads::set_current_thread(thread);

    JavaNativeInterface::callStaticVoidMethod(klass, method);
}
