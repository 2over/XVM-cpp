//
// Created by xiehao on 2024/12/13.
//

#ifndef XVM_CPP_HEAPWORD_H
#define XVM_CPP_HEAPWORD_H


#include "../../../include/memory/memory_cell.h"

class HeapWord {

private:
    MemoryCell *cell;
    void *i;

public:
    HeapWord(MemoryCell *p) {
        cell = p;
        i = cell->ptr();
    }

    char *value() {
        return (char *) i;
    }
};


#endif //XVM_CPP_HEAPWORD_H
