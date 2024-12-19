//
// Created by xiehao on 2024/12/19.
//

#ifndef XVM_CPP_JAVANATIVEINTERFACE_H
#define XVM_CPP_JAVANATIVEINTERFACE_H


#include "../oops/MethodInfo.h"
#include "../oops/InstanceKlass.h"

class JavaNativeInterface {
public:
    static MethodInfo *getMethodID(InstanceKlass *klass, string method_name, string descriptor_name);

    static MethodInfo *getVMethodID(InstanceKlass *klass, string method_name, string descriptor_name);

    static void callStaticVoidMethod(InstanceKlass *klass, MethodInfo *method, ...);

    static void callVoidMethod(InstanceKlass *klass, MethodInfo *method, ...);

};


#endif //XVM_CPP_JAVANATIVEINTERFACE_H
