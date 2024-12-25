//
// Created by xiehao on 2024/12/24.
//

#include "ClassLoaderDataGraph.h"
#include "../../../include/common.h"
#include "Java_lang_ClassLoader.h"
#include "ClassLoaderData.h"

ClassLoaderData *ClassLoaderDataGraph::_head = NULL;

ClassLoaderData *ClassLoaderDataGraph::find_or_create(ClassLoader *class_loader) {
    ClassLoaderData *loader_data = Java_lang_ClassLoader::loader_data(class_loader);
    if (loader_data) {
        return loader_data;
    }

    return ClassLoaderDataGraph::add(class_loader, false);
}

ClassLoaderData *ClassLoaderDataGraph::add(ClassLoader *class_loader, bool anonymous) {
    ClassLoaderData::Dependencies dependencies(NULL);
    ClassLoaderData *loader_data = new ClassLoaderData(class_loader, anonymous, dependencies);
    *Java_lang_ClassLoader::loader_data_addr(class_loader) = loader_data;

    _head = loader_data;
    loader_data->_next = _head;
    return loader_data;
}