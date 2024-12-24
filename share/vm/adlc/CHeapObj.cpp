//
// Created by xiehao on 2024/12/13.
//

#include "CHeapObj.h"

void* CHeapObj::operator new(size_t size) {
    return (void *)malloc(size);
}

void CHeapObj::operator delete(void *p) {
    free(p);
}