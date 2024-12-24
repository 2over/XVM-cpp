//
// Created by ziya on 2024/12/23.
//

#ifndef XVM_CPP_BLOCKFREELIST_H
#define XVM_CPP_BLOCKFREELIST_H

#include "../../../include/common.h"

class BlockFreelist {
private:
    void *_dictionary;

public:
    BlockFreelist();

    ~BlockFreelist() {};
};


#endif //XVM_CPP_BLOCKFREELIST_H
