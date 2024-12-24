//
// Created by xiehao on 2024/12/3.
//

#ifndef XVM_CPP_KLASS_H
#define XVM_CPP_KLASS_H
#include "Metadata.h"

class ClassLoaderData;


class Klass : public Metadata{

public:
    Klass() {}

    void* operator new(size_t size) {};

    void* operator new(size_t size, ClassLoaderData* loader_data, size_t word_size);
};


#endif //XVM_CPP_KLASS_H
