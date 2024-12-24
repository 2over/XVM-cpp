//
// Created by ziya on 2024/12/20.
//

#include "SystemDictionary.h"
#include "../oops/Klass.h"
#include "../classfile/ClassLoader.h"
#include "../classfile/ClassLoaderData.h"
#include "../oops/InstanceKlass.h"
#include "ClassLoaderDataGraph.h"
#include "../../../include/jni/JniTools.h"

extern JNIEnv* g_env;

Dictionary* SystemDictionary::_dictionary = NULL;

void SystemDictionary::initialize() {
    _dictionary = new Dictionary;
}

Klass* SystemDictionary::resolve_or_null(string class_name) {
    // TODO 判断是不是数组
    return resolve_instance_class_or_null(class_name);
}

Klass* SystemDictionary::resolve_instance_class_or_null(string class_name) {
    Klass* klass = NULL;

    klass =reinterpret_cast<Klass*>(dictionary()->find(class_name));
    if (NULL != klass) {
        return klass;
    }

    klass = ClassLoader::load_classfile(class_name);
    if (NULL == klass) {
        ERROR_PRINT("不存在的文件: %s\n", class_name.c_str());
        exit(-1);
    }

    dictionary()->add(class_name, reinterpret_cast<long>(klass));
    return klass;

}

void SystemDictionary::load_super_class(Klass *klass) {
    InstanceKlass* instance = static_cast<InstanceKlass *>(klass);

    int index = instance->super_class();
    string super_class_name = instance->constant_pool()->get_super_class_name(index);
    if ("java/lang/Object" == super_class_name) {
        INFO_PRINT("不加载: java/lang/Object\n");
        return;
    }

    INFO_PRINT("%s\n", super_class_name.c_str());
}

Klass *SystemDictionary::resolve_from_stream(ClassLoader *class_loader) {
    ClassLoaderData* loader_data = register_loader(class_loader);

    Klass* k = new (loader_data, sizeof(Klass))Klass();

    return NULL;
}

ClassLoaderData* SystemDictionary::register_loader(ClassLoader *class_loader) {
    if (NULL == class_loader) {
        return ClassLoaderData::the_null_class_loader_data();
    }

    return ClassLoaderDataGraph::find_or_create(class_loader);
}

