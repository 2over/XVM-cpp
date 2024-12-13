//
// Created by xiehao on 2024/12/13.
//

#ifndef XVM_CPP_CHEAPOBJ_H
#define XVM_CPP_CHEAPOBJ_H

#include "../../../include/common.h"


class CHeapObj {
public:
    void *operator new(size_t size);

    void operator delete(void *p);
};


#endif //XVM_CPP_CHEAPOBJ_H
