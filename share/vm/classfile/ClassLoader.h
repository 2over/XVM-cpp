//
// Created by ziya on 2024/12/20.
//

#ifndef XVM_CPP_CLASSLOADER_H
#define XVM_CPP_CLASSLOADER_H

#include "../../../include/common.h"

class Klass;

class ClassLoaderData;

class ClassLoader {
private:
    ClassLoaderData *_loader_data;
private:
    // TODO 需要调整成自己的 target/classes/
    string path = "target/classes";

public:
    ClassLoader() : _loader_data(NULL) {

    }

public:
    static Klass *load_classfile(string class_name);

public:
    ClassLoaderData *loader_data();

    ClassLoaderData **loader_data_addr();
};


#endif //XVM_CPP_CLASSLOADER_H
