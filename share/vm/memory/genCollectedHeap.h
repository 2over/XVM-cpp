//
// Created by xiehao on 2024/12/13.
//

#ifndef XVM_CPP_GENCOLLECTEDHEAP_H
#define XVM_CPP_GENCOLLECTEDHEAP_H

#include "genCollectorPolicy.h"
#include "sharedHeap.h"
#include "../../../include/memory/memory_pool.h"
#include "../utilities/HeapWord.h"

class GenCollectedHeap : public SharedHeap {

protected:
    static GenCollectedHeap *_gch;

private:
    GenCollectorPolicy *_gen_policy;

    int _n_gens;
    MemoryChunk **_gens;
    MemoryPool *_memory_pool;
public:
    GenCollectedHeap(GenCollectorPolicy *policy);

    void intialize();

    void post_initialize();

    HeapWord *mem_allocate(size_t size);

    HeapWord *attempt_allocation(size_t size);

    static GenCollectedHeap *heap();

public:
    MemoryChunk *get_gen(int i) const {
        return _gens[i];
    }

    GenCollectorPolicy *gen_policy() const {
        return _gen_policy;
    }

    CollectorPolicy *collector_policy() const {
        return (CollectorPolicy *) gen_policy();
    }

    HeapWord *satisfy_failed_allocation(std::size_t size);

    void do_collection(bool is_new);

    void do_full_collection();
};


#endif //XVM_CPP_GENCOLLECTEDHEAP_H
