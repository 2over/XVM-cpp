//
// Created by ziya on 2024/12/25.
//

#ifndef XVM_CPP_VMTHREAD_H
#define XVM_CPP_VMTHREAD_H


#include "NameThread.h"
#include "VM_Operation.h"
#include "VMOperationQueue.h"

class VMThread: public NameThread {
public:
    static void execute(VM_Operation* op);

private:
    // VM_Operation support
    static VM_Operation*        _cur_vm_operation;  // Current VM Operation
    static VMOperationQueue*    _vm_queue;          // Queue (w /policy) of VM operations

    void run();
    void loop();
    void evaluate_operation(VM_Operation* op);

};


#endif //XVM_CPP_VMTHREAD_H
