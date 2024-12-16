//
// Created by xiehao on 2024/12/13.
//

#include "genCollectedHeap.h"
#include "DefNewGeneration.h"
#include "../../../include/gc/gc_factory.h"

GenCollectedHeap* GenCollectedHeap::_gch;

GenCollectedHeap::GenCollectedHeap(GenCollectorPolicy *policy): _gen_policy(policy) {
    _n_gens = 2;
}

void GenCollectedHeap::initialize() {
    _memory_pool = new MemoryPool;

    _gens = (MemoryChunk **)calloc(sizeof(MemoryChunk*), _n_gens);

    _gens[0] = _memory_pool->new_chunk(1024);
    _gens[1] = _memory_pool->new_chunk(1024 * 2);

    _gch = this;
}

void GenCollectedHeap::post_initialize() {

}

HeapWord* GenCollectedHeap::mem_allocate(size_t size) {
    return gen_policy()->mem_allocate_work(size);
}

GenCollectedHeap *GenCollectedHeap::heap() {
    return _gch;
}

HeapWord* GenCollectedHeap::satisfy_failed_allocation(std::size_t size) {
    return gen_policy()->satisfy_failed_allocation(size);
}

void GenCollectedHeap::do_collection(bool is_new) {
    if (is_new) {
        GCFactory::get_instance()->minor_run(DEFAULT_GC_TYPE, _gens[0]);
    } else {
        GCFactory::get_instance()->minor_run(DEFAULT_GC_TYPE, _gens[1]);
    }
}

void GenCollectedHeap::do_full_collection() {

    // full gc, 新生代 老年代全进行回收
    // TODO: 实现卡表，解决老年代对新生代的引用
    for (int i = 0; i < _n_gens; i++) {
        GCFactory::get_instance()->minor_run(DEFAULT_GC_TYPE, _gens[i]);
    }
}

