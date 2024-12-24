//
// Created by xiehao on 2024/12/24.
//

#include "Java_lang_ClassLoader.h"
#include "ClassLoader.h"
#include "ClassLoaderData.h"


 ClassLoaderData *Java_lang_ClassLoader::loader_data(ClassLoader *loader) {
    return loader->loader_data();
}

ClassLoaderData **Java_lang_ClassLoader::loader_data_addr(ClassLoader *loader) {
    return loader->loader_data_addr();
}





