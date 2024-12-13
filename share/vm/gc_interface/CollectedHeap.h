//
// Created by xiehao on 2024/12/13.
//

#ifndef XVM_CPP_COLLECTEDHEAP_H
#define XVM_CPP_COLLECTEDHEAP_H

#include "../adlc/CHeapObj.h"
#include "../utilities/HeapWord.h"
#include "../oops/oopDesc.h"

class CollectedHeap : public CHeapObj {
public:
    static OopDesc *obj_allocate(size_t size);

    static HeapWord *common_mem_allocate_init(size_t size);

private:
    static HeapWord *common_mem_allocate_noinit(size_t size);
};


#endif //XVM_CPP_COLLECTEDHEAP_H
