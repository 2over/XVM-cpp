//
// Created by ziya on 2024/12/13.
//

#include "genCollectorPolicy.h"

#include "../memory/genCollectedHeap.h"

HeapWord* GenCollectorPolicy::mem_allocate_work(size_t size) {
    GenCollectedHeap *gch = GenCollectedHeap::heap();

    // TODO Cover
    MemoryChunk *gen0 = = gch->get_
}
