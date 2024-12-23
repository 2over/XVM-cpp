//
// Created by xiehao on 2024/12/3.
//

#include "Klass.h"
#include "../memory/Metaspace"

void* Klass::operator new(size_t size, ClassLoaderData *loader_data, size_t) {
    return Metaspace::allocate(loader_data, word_size, /** read_only */ false, MetaspaceObj::ClassType)
}