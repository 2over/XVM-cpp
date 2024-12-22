//
// Created by ziya on 2024/12/20.
//

#include "ClassLoader.h"
#include "ClassPathDirEntry.h"
#include "ClassFileParser.h"

Klass* ClassLoader::load_classfile(string class_name) {
    Klass* klass = NULL;
    ClassPathDirEntry* e = new ClassPathDirEntry;
    ClassFileStream* stream = e->open_stream(class_name);

    if (NULL != stream) {
        ClassFileParser parser(stream);

        klass = parser.parseClassFile();
    }

    return klass;

}

ClassLoaderData *ClassLoader::loader_data() {
    return _loader_data;
}

ClassLoaderData **ClassLoader::loader_data_addr() {
    return &_loader_data;
}
