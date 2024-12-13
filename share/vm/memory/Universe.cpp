//
// Created by xiehao on 2024/12/13.
//

#include "Universe.h"
#include "../../../include/common.h"

CollectedHeap* Universe::_collectedHeap = NULL;

void Universe::initialize_heap() {

    INFO_PRINT("initialize_heap\n");

    if (UseParallelGC) {

    } else if (UseG1GC) {

    } else {
        GenColl
    }
}