//
// Created by ziya on 2024/12/13.
//

#ifndef XVM_CPP_DEFNEWGENERATION_H
#define XVM_CPP_DEFNEWGENERATION_H
#include "Generation.h"
#include "../utilities/HeapWord.h"
#include "../../../include/common.h"

class DefNewGeneration :public Generation {
public:
    HeapWord* par_allocate(size_t size);

    // this is a test commit
};


#endif //XVM_CPP_DEFNEWGENERATION_H
