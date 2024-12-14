//
// Created by ziya on 2024/12/13.
//

#ifndef XVM_CPP_GENCOLLECTORPOLICY_H
#define XVM_CPP_GENCOLLECTORPOLICY_H

#include "collectorPolicy.h"
#include "../utilities/HeapWord.h"


class GenCollectorPolicy : public CollectorPolicy {

public:
    HeapWord* mem_allocate_work(size_t size);

    HeapWord* satisfy_failed_allocation(size_t size);
};


#endif //XVM_CPP_GENCOLLECTORPOLICY_H
