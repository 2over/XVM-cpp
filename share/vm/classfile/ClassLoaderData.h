//
// Created by ziya on 2024/12/23.
//

#ifndef XVM_CPP_CLASSLOADERDATA_H
#define XVM_CPP_CLASSLOADERDATA_H

#include "../../../include/common.h"

class ClassLoader;

class ClassLoaderDataGraph;

class Metaspace;

class JavaThread;

class ClassLoaderData {
    friend class ClassLoaderDataGraph;

private:
    class Dependencies {
        objArrayOop _list_head;
    public:
        Dependencies() : _list_head(NULL) {}

        Dependencies(JavaThread *java_thread) : _list_head(NULL) {

        }
    };

private:
    static ClassLoaderData *_the_null_class_loader_data;
    ClassLoaderData *_next;
    ClassLoader *_class_loader;
    Metaspace *_metaspace;
    bool _is_anonymous;
    Dependencies _dependencies;
public:
    ClassLoaderData(ClassLoader *class_loader, bool is_anonymous, Dependencies dependencies) :
            _class_loader(class_loader), _metaspace(NULL), _is_anonymous(is_anonymous), _dependencies(dependencies) {

    }
};


#endif //XVM_CPP_CLASSLOADERDATA_H
