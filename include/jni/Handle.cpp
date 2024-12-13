//
// Created by xiehao on 2024/12/3.
//

#include "Handle.h"

static jobject dataToHandle(JNIEnv *env, jlong data, int data_type) {
    // 找到Handle类
    const char *handle_class_name = "com/cover/jvm/jdk/classes/Handle";

    jclass c = env->FindClass(handle_class_name);

    if (NULL == c) {
        ERROR_PRINT("不存在的类: %s\n", handle_class_name);
        exit(-1);
    }

    // 找到构造方法
    jmethodID construct = env->GetMethodID(c, "<init>", "()V");
    if (NULL == construct) {
        ERROR_PRINT("该类不存在默认构造方法: %s\n", handle_class_name);
        exit(-1);
    }

    // 创建对象
    jobject obj = env->NewObject(c, construct);
    if (NULL == obj) {
        ERROR_PRINT("创建对象失败: %s\n", handle_class_name);
        exit(-1);
    }

    // 获取属性 [p]
    jfieldID p = env->GetFieldID(c, "p", "J");
    if (NULL == p) {
        ERROR_PRINT("该类不存在属性 [ p ]: %s\n", handle_class_name);
        exit(-1);
    }

    // 给属性 [p] 赋值
    env->SetLongField(obj, p, data);

    // 获取属性 [type]
    jfieldID type = env->GetFieldID(c, "type", "I");
    if (NULL == type) {
        ERROR_PRINT("该类不存在属性 [ type ] : %s\n", handle_class_name);
        exit(-1);
    }

    // 给属性 [type]  赋值
    env->SetIntField(obj, type, data_type);

    return obj;

}

template<typename T>
static T handleToData(JNIEnv *env, jobject handle) {
    jclass c = env->GetObjectClass(handle);

    // 获取属性 [p]
    jfieldID p = env->GetFieldID(c, "p", "J");
    if (NULL == p) {
        ERROR_PRINT("该类不存在属性 [p]\n");
        exit(-1);
    }

    jlong p_val = env->GetLongField(handle, p);
    return (T) p_val;
}

jobject Handle::klassToHandle(JNIEnv *env, Klass *klass) {
    jlong data = reinterpret_cast<jlong>(klass);

    return dataToHandle(env, data, HANDLE_TYPE_KLASS);
}

jobject Handle::methodToHandle(JNIEnv *env, MethodInfo *method) {
    jlong data = reinterpret_cast<jlong>(method);
    return dataToHandle(env, data, HANDLE_TYPE_METHOD);
}

Klass *Handle::klass(JNIEnv *env, jobject klass_handle) {
    return handleToData<Klass *>(env, klass_handle);
}

MethodInfo *Handle::method(JNIEnv *env, jobject method_handle) {
    return handleToData<MethodInfo *>(env, method_handle);
}