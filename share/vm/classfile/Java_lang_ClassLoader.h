//
// Created by xiehao on 2024/12/24.
//

#ifndef XVM_CPP_JAVA_LANG_CLASSLOADER_H
#define XVM_CPP_JAVA_LANG_CLASSLOADER_H

class ClassLoader;

class ClassLoaderData;

class Java_lang_ClassLoader {
public:
    static ClassLoaderData **loader_data_addr(ClassLoader *loader);

    static ClassLoaderData *loader_data(ClassLoader *loader);
};


#endif //XVM_CPP_JAVA_LANG_CLASSLOADER_H
