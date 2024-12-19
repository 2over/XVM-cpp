//
// Created by xiehao on 2024/12/13.
//

#ifndef XVM_CPP_UNIVERSE_H
#define XVM_CPP_UNIVERSE_H

#include "../adlc/AllStatic.h"
#include "../../../include/common.h"
#include "../gc_interface/CollectedHeap.h"

class Universe : public AllStatic {
private:
    static CollectedHeap *_collectedHeap;

public:
    static CollectedHeap *heap() {
        return _collectedHeap;
    }

public:
    static void initialize_heap();
};


#endif //XVM_CPP_UNIVERSE_H
