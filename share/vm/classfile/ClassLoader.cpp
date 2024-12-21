//
// Created by ziya on 2024/12/20.
//

#include "ClassLoader.h"

Klass* ClassLoader::load_classfile(string class_name) {
    Klass* klass = NULL;
    ClassPathDirEntry* stream = e->open_stream(class_name);
}
