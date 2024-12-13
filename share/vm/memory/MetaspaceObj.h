//
// Created by xiehao on 2024/12/13.
//

#ifndef XVM_CPP_METASPACEOBJ_H
#define XVM_CPP_METASPACEOBJ_H


#include "../../../include/common.h"
#include "../../../share/vm/memory/Universe.h"

class MetaspaceObj {
public:
    void* operator new (size_t size) {
        INFO_PRINT("从元空间分配内存: %d\d", size);
        HeapWord* v = Universe::heap()->common_mem_allocate_init(size);

        return v->value();
    }
};


#endif //XVM_CPP_METASPACEOBJ_H
