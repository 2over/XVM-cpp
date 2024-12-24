//
// Created by ziya on 2024/12/13.
//

#include "genCollectorPolicy.h"

#include "../memory/genCollectedHeap.h"

HeapWord *GenCollectorPolicy::mem_allocate_work(size_t size) {
    GenCollectedHeap *gch = GenCollectedHeap::heap();

    MemoryChunk *gen0 = gch->get_gen(0);

    MemoryCell *obj = gen0->malloc(size);
    if (NULL == obj) {
        // 触发GC后再分配
        ERROR_PRINT("分配内存失败\n");

        exit(-1);
    }

    return new HeapWord(obj);
}

HeapWord *GenCollectorPolicy::satisfy_failed_allocation(size_t size) {
    return NULL;
}
