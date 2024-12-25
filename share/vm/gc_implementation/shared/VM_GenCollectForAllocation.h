//
// Created by ziya on 2024/12/25.
//

#ifndef XVM_CPP_VM_GENCOLLECTFORALLOCATION_H
#define XVM_CPP_VM_GENCOLLECTFORALLOCATION_H


#include "VM_GC_Operation.h"
#include "../../utilities/HeapWord.h"

class VM_GenCollectForAllocation : public VM_GC_Operation{
private:
    HeapWord*   _res;
    size_t      _size;          // size of object to be allocated
    bool        _tlab;
public:
    VM_GenCollectForAllocation(size_t size): _size(size) {
        _res = NULL;
    }

    ~VM_GenCollectForAllocation() {}

    void doit();

    HeapWord* result() const {
        return _res;
    }

};


#endif //XVM_CPP_VM_GENCOLLECTFORALLOCATION_H
