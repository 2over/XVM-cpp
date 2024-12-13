//
// Created by xiehao on 2024/12/13.
//

#include "oopDesc.h"
#include "../memory/genCollectedHeap.h"
#include "../memory/Universe.h"

OopDesc* CollectedHeap::obj_allocate(size_t size) {
    HeapWord* obj = common_mem_allocate_init(size);
    return (OopDesc*)(obj->value());
}

HeapWord* CollectedHeap::common_mem_allocate_init(size_t size) {
    HeapWord* obj = common_mem_allocate_noinit(size);
    return obj;
}

HeapWord* CollectedHeap::common_mem_allocate_noinit(size_t size) {
    HeapWord* result = NULL;

    // TODO 先尝试从TLAB中分配，后面实现

    // 直接去堆中-新生代分配
    GenCollectedHeap* heap = (GenCollectedHeap*)Universe::heap();

    result = heap->mem_allocate(size);

    if (NULL == result) {
        // OOM print
    }

    return result;
}
