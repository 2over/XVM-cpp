//
// Created by xiehao on 2024/12/13.
//

#ifndef XVM_CPP_ALLSTATIC_H
#define XVM_CPP_ALLSTATIC_H

#include "../../../include/common.h"

class AllStatic {
public:
    void *operator new(size_t size);

    void operator delete(void *p);
};


#endif //XVM_CPP_ALLSTATIC_H
