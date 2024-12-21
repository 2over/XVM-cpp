//
// Created by ziya on 2024/12/20.
//

#include "SystemDictionary.h"
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
}

