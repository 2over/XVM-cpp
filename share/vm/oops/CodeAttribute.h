//
// Created by ziya on 2024/12/19.
//

#ifndef XVM_CPP_CODEATTRIBUTE_H
#define XVM_CPP_CODEATTRIBUTE_H

#include "Attribute.h"
#include "MethodInfo.h"
#include "../code/CodeStream.h"

struct ExceptionTableItem {
    short start_pc;
    short end_pc;
    short handler_gc;
    short catch_types;
};


class CodeAttribute : public Attribute{

private:
    MethodInfo* _belong_method;

    short                    _name_index;
    int                     _length;
    short                   _max_locals;
    int                     _code_length;
    CodeStream*             _codes;

    short                   _exception_table_length;
    ExceptionTableItem*     _exception_table;

    short                   _attributes_count;
    LocalVariableTable*     _local_variable_table;

};


#endif //XVM_CPP_CODEATTRIBUTE_H
