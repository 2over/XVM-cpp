//
// Created by xiehao on 2024/12/3.
//

#ifndef XVM_CPP_HANDLE_H
#define XVM_CPP_HANDLE_H

#include "../common.h"
#include "jni.h"
#include "../../share/vm/oops/Klass.h"
#include "../../share/vm/oops/MethodInfo.h"


class Handle {
public:
    enum Type {
        HANDLE_TYPE_KLASS = 1,
        HANDLE_TYPE_OOP = 2,
        HANDLE_TYPE_METHOD = 3
    };

public:
    static jobject klassToHandle(JNIEnv *env, Klass *klass);

    static jobject methodToHandle(JNIEnv *env, MethodInfo *method);

    static Klass *klass(JNIEnv *env, jobject klass_handle);

    static MethodInfo *method(JNIEnv *env, jobject method_handle);
};


#endif //XVM_CPP_HANDLE_H
