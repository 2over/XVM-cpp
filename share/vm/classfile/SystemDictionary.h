//
// Created by ziya on 2024/12/20.
//

#ifndef XVM_CPP_SYSTEMDICTIONARY_H
#define XVM_CPP_SYSTEMDICTIONARY_H

#include "Dictionary.h"
#include "../oops/Klass.h"

class ClassLoader;

class ClassLoaderData;

class SystemDictionary {
    static Dictionary *_dictionary;

public:
    static void initialize();

    static Dictionary *dictionary() {
        return _dictionary;
    }

public:
    static Klass *resolve_or_null(string class_name);

    static Klass *resolve_instance_class_or_null(string class_name);

    static void load_super_class(Klass *klass);

    static Klass *resolve_from_stream(ClassLoader *class_loader);

    static ClassLoaderData *register_loader(ClassLoader *class_loader);

};


#endif //XVM_CPP_SYSTEMDICTIONARY_H
