//
// Created by ziya on 2024/12/13.
//

#ifndef XVM_CPP_GENERATION_H
#define XVM_CPP_GENERATION_H

#include "../utilities/HeapWord.h"
#include "../../../include/common.h"

class Generation {

    virtual HeapWord *aollocate(size_t word_size, bool is_tlab) = 0;

    virtual HeapWord *par_allocate(size_t word_size, bool is_tlab) = 0;
};


#endif //XVM_CPP_GENERATION_H
