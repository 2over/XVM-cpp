//
// Created by ziya on 2024/12/16.
//

#include "InstanceKlass.h"
#include "../prims/JavaNativeInterface.h"
#include "../classfile/SystemDictionary.h"

instanceOop InstanceKlass::allocate_instance(size_t size) {
    instanceOop i = (instanceOop) CollectedHeap::obj_allocate(size);

    return i;
}

int InstanceKlass::get_interfaces_count() {
    return _interfaces_count;
}

void InstanceKlass::initialize() {
    if (should_be_initialized()) {
        initialize_impl();
    }
}

void InstanceKlass::initialize_impl() {
    MethodInfo *clinit_method = JavaNativeInterface::getMethodID(this,
                                                                 "<clinit>", "()V");

    if (NULL == clinit_method) {
        return;
    }

    JavaNativeInterface::callStaticVoidMethod(this, clinit_method);
}

void InstanceKlass::link_class() {
    if (!is_linked()) {
        link_class_impl(this);
    }
}

void InstanceKlass::link_class_impl(InstanceKlass *klass) {
    if (klass->is_in_error_state()) {
        ERROR_PRINT("link class 出错\n");
        exit(-1);
    }

    if (klass->is_linked()) {
        INFO_PRINT("已完成link\n");

        return;
    }

    // 触发父类加载
    if (NULL == klass->super_klass()) {
        string super_class_name = klass->constant_pool()->get_super_class_name(klass->super_class());
        if (0 == super_class_name.find("java")) { // 系统类，不加载
            WARNING_PRINT("系统类, 不加载: %s\n", super_class_name.c_str());

            klass->initialize_vtable(this);

            return;
        }

        INFO_PRINT("触发父类加载: %s\n", super_class_name.c_str());

        InstanceKlass *instanceKlass = static_cast<InstanceKlass *>(SystemDictionary::resolve_or_null(
                super_class_name));

        klass->set_super_klass(instanceKlass);

        link_class_impl(instanceKlass);

    }

    // TODO 触发接口装载
    // 向vtable中插入数据
    klass->initialize_vtable(this);

    // TOOD 向itable中插入数据

    // 设置状态
    klass->set_init_state(linked);
}

void InstanceKlass::initialize_super_vtable(InstanceKlass *klass) {
    InstanceKlass *super_klass = static_cast<InstanceKlass *>(klass->super_klass());

    // 如果父类是Object, 那super_klass = NULL, 这样就会报错super_klass->super_klass().得处理
    if (NULL == super_klass) {
        INFO_PRINT("没有父类了, 开始插入vtable\n");

        return;
    } else {
        if (NULL != super_klass->super_klass()) {
            INFO_PRINT("还有父类, %s\n", super_klass->name().c_str());

            initialize_super_vtable(super_klass);
        } else {
            INFO_PRINT("没有父类了, 开始插入vtable, %s\n", super_klass->name().c_str());
        }
    }

    // 先将父类的符合条件的方法写入vtable
    vector<MethodInfo *> methods = super_klass->methods();
    for (vector<MethodInfo *>::iterator iter = methods.begin(); iter != methods.end(); iter++) {
        MethodInfo *method = *iter;

        // 只有protected、public修饰且不被static、final修饰的方法写入vtable
        if (method->flags()->is_protected() || method->flags()->is_public()) {
            // 跳过构造方法、静态代码块
            if ("<init>" == method->name() || "<clinit>" == method->name()) {
                INFO_PRINT("跳过方法init、clinit: %s\n", method->name().c_str());
                continue;
            }

            // 跳过final、 static
            if (method->flags()->is_final() || method->flags()->is_static()) {
                INFO_PRINT("跳过方法final、static: %s\n", method->name().c_str());

                continue;
            }

            // 加入vtable
            INFO_PRINT("\t 插入vtable中的方法: %s\n", method->name().c_str());

            vtable().push_back(*iter);
        } else {
            INFO_PRINT("不加入vtable中的方法: %s\n", method->name().c_str());
        }

    }
}

void InstanceKlass::initialize_vtable(InstanceKlass *klass) {
    initialize_super_vtable(klass);

    vector<MethodInfo *> methods = klass->methods();
    for (vector<MethodInfo *>::iterator iter = methods.begin(); iter != methods.end(); iter++) {
        MethodInfo *method = *iter;
        // 只有protected、public修饰且不被static、final修饰的方法写入vtable
        if (method->flags()->is_protected() || method->flags()->is_public()) {
            // 跳过构造方法，静态代码块
            if ("<init>" == method->name() || "<clinit>" == method->name()) {
                INFO_PRINT("跳过方法init、clinit: %s\n", method->name().c_str());

                continue;
            }

            // 跳过final、 static
            if (method->flags()->is_final() || method->flags()->is_static()) {
                INFO_PRINT("跳过方法final、static: %s\n", method->name().c_str());

                continue;
            }

            // 加入vtable
            INFO_PRINT("\t 插入vtable中的方法: %s\n", method->name().c_str());
            vtable().push_back(*iter);
        } else {
            INFO_PRINT("不加入vtable中的方法: %s\n", method->name().c_str());
        }
    }
}

void InstanceKlass::print_vtable() {
    vector<MethodInfo *> methods = vtable();
    for (int i = 0; i < methods.size(); i++) {
        MethodInfo *tmp = methods[i];

        INFO_PRINT("%s, %s, %s\n", tmp->class_name().c_str(), tmp->name().c_str(), tmp->descriptor().c_str());
    }
}

void InstanceKlass::print_methods() {
    vector<MethodInfo *> methods = this->methods();
    for (int i = 0; i < methods.size(); i++) {
        MethodInfo *tmp = methods[i];

        INFO_PRINT("%s, %s, %s\n", tmp->class_name().c_str(), tmp->name().c_str(), tmp->descriptor().c_str());
    }
}




