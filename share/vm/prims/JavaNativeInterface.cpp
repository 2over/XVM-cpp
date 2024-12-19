//
// Created by xiehao on 2024/12/19.
//

#include "JavaNativeInterface.h"
MethodInfo* JavaNativeInterface::getMethodID(InstanceKlass *klass, string method_name, string descriptor_name) {
    vector<MethodInfo *> methods = klass->methods();
    MethodInfo* ret = NULL;

    for (int i = 0; i < methods.size(); ++i) {
        MethodInfo* tmp = methods[i];

        if ((tmp->name() == method_name) && (tmp->descriptor() == descriptor_name)) {
            ret = tmp;
        }
    }

    return ret;
}

MethodInfo * JavaNativeInterface::getVMethodID(InstanceKlass *klass, string method_name, string descriptor_name) {
    vector<MethodInfo *> methods = klass->vtable();
    MethodInfo* ret = NULL;

    for (int i = 0; i < methods.size(); ++i) {
        MethodInfo *tmp = methods[i];

        if ((tmp->name() == method_name) && (tmp->descriptor() == descriptor_name)) {
            ret = tmp;
        }
    }

    return ret;
}

void JavaNativeInterface::callStaticVoidMethod(InstanceKlass *klass, MethodInfo *method, ...) {
    JavaThread* tjread = Threads::current_
}