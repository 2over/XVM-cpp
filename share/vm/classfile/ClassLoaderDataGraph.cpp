//
// Created by xiehao on 2024/12/24.
//

#include "ClassLoaderDataGraph.h"
#include "../../../include/common.h"
#include "Java_lang_ClassLoader.h"
#include "ClassLoaderData.h"

ClassLoaderData* ClassLoaderDataGraph::_head = NULL;

ClassLoaderData* ClassLoaderDataGraph::find_or_create(ClassLoader *class_loader) {
    ClassLoaderData* loader_data = Java_lang_ClassLoader::loader_data(class_loader);
    if (loader_data) {
        return loader_data;
    }

    return ClassLoaderDataGraph::add(class_loader, false);
}
