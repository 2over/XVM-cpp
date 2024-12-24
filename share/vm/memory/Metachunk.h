//
// Created by ziya on 2024/12/23.
//

#ifndef XVM_CPP_METACHUNK_H
#define XVM_CPP_METACHUNK_H


#include "../../../include/memory/memory_chunk.h"

class Metachunk : public MemoryChunk {
public:
    MetaWord *allocate(size_t word_size);

};


#endif //XVM_CPP_METACHUNK_H
