//
// Created by xiehao on 2024/12/13.
//

#include "Universe.h"
#include "../../../include/common.h"
#include "genCollectedHeap.h"
#include "MarkSweepPolicy.h"

CollectedHeap *Universe::_collectedHeap = NULL;

void Universe::initialize_heap() {

    INFO_PRINT("initialize_heap\n");

    if (UseParallelGC) {

    } else if (UseG1GC) {

    } else {

        GenCollectorPolicy *gc_policy;
        if (UseSerialGC) {

        } else if (UseConcMarkSweepGC) {

        } else {
            gc_policy = new MarkSweepPolicy();
        }

        GenCollectedHeap *heap = new GenCollectedHeap(gc_policy);

        Universe::_collectedHeap = heap;
        heap->initialize();

    }


}