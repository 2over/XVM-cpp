//
// Created by xiehao on 2024/12/19.
//

#ifndef XVM_CPP_VIRTUALFRAME_H
#define XVM_CPP_VIRTUALFRAME_H


#include "StackValue.h"
#include "../../../include/common.h"

class VirtualFrame {

public:
    StackValue **_local_variable_table;
    stack<StackValue *> _operand_stack;

public:
    VirtualFrame(int local_table_size) {
        _local_variable_table = new StackValue *[local_table_size];
    }

    ~VirtualFrame() {
        if (NULL != _local_variable_table) {
            delete[] _local_variable_table;
        }
    }

    StackValue **local_variable_table() {
        return _local_variable_table;
    }

    stack<StackValue *> &operand_stack() {
        return _operand_stack;
    }


};


#endif //XVM_CPP_VIRTUALFRAME_H
