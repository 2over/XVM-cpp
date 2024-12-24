//
// Created by xiehao on 2024/12/24.
//

#ifndef XVM_CPP_CLASSLOADERDATAGRAPH_H
#define XVM_CPP_CLASSLOADERDATAGRAPH_H

class ClassLoader;

class ClassLoaderData;

class ClassLoaderDataGraph {
private:
    static ClassLoaderData *_head;

private:
    static ClassLoaderData *add(ClassLoader *class_loader, bool anonymous);

public:
    static ClassLoaderData *find_or_create(ClassLoader *class_loader);
};


#endif //XVM_CPP_CLASSLOADERDATAGRAPH_H
