//
// Created by ziya on 2024/12/25.
//

#include "VMThread.h"
#include "../memory/genCollectedHeap.h"
#include "../memory/Universe.h"

VM_Operation*       VMThread::_cur_vm_operation = NULL;
VMOperationQueue*   VMThread::_vm_queue         = NULL;

void VMThread::execute(VM_Operation *op) {
    INFO_PRINT("start gc. ....\n");
    GenCollectedHeap* heap = (GenCollectedHeap *) Universe::heap();

    heap->do_full_collection();
}

void VMThread::run() {
    this->loop();
}

void VMThread::loop() {

}

void VMThread::evaluate_operation(VM_Operation *op) {

}
