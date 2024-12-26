//
// Created by ziya on 2024/12/25.
//

#ifndef XVM_CPP_VMOPERATIONQUEUE_H
#define XVM_CPP_VMOPERATIONQUEUE_H

#include "../adlc/CHeapObj.h"
#include "VM_Operation.h"
#include <queue>

class VMOperationQueue : public CHeapObj {
private:
    queue<VM_Operation *> _container;


};


#endif //XVM_CPP_VMOPERATIONQUEUE_H
