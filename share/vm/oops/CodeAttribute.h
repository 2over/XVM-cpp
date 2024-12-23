//
// Created by ziya on 2024/12/19.
//

#ifndef XVM_CPP_CODEATTRIBUTE_H
#define XVM_CPP_CODEATTRIBUTE_H

#include "Attribute.h"
#include "MethodInfo.h"
#include "../code/CodeStream.h"
#include "LocalVariableTable.h"
#include "LineNumberTable.h"
#include "../classfile/StackMapTable.h"

struct ExceptionTableItem {
    short start_pc;
    short end_pc;
    short handler_pc;
    short catch_type;
};


class CodeAttribute : public Attribute{

private:
    MethodInfo* _belong_method;

    short                    _name_index;
    int                     _length;
    short                   _max_locals;
    short                   _max_stack;
    int                     _code_length;
    CodeStream*             _codes;

    short                   _exception_table_length;
    ExceptionTableItem*     _exception_table;

    short                   _attributes_count;
    LocalVariableTable*     _local_variable_table;
    LineNumberTable*        _line_number_table;
    StackMapTable*          _stack_map_table;

    string                  _name;

public:
    CodeAttribute() {}
    CodeAttribute(MethodInfo* method) {
        _belong_method = method;
    }

    CodeStream* codes() const {
        return _codes;
    }

    ExceptionTableItem* exception_table() const {
        return _exception_table;
    }

    ~CodeAttribute() {
        if (NULL != _codes) {
            delete _codes;
        }

        if (NULL != _exception_table) {
            delete _exception_table;
        }
    }

public:
    void set_name_index(short index) {
        _name_index = index;
    }

    void set_length(int len) {
        _length = len;
    }

    void set_max_stack(short v) {
        _max_stack = v;
    }

    void set_max_locals(short v) {
        _max_locals = v;
    }

    void set_code_length(short v) {
        _code_length = v;
    }

    void set_codes(CodeStream *stream) {
        _codes = stream;
    }

    void set_exception_table_length(short v) {
        _exception_table_length = v;
    }

    void create_exception_table() {
        _exception_table = new ExceptionTableItem[_exception_table_length];
    }

    void set_attributes_count(short v) {
        _attributes_count = v;
    }

    void set_local_variable_table(LocalVariableTable* table) {
        _local_variable_table = table;
    }

    void set_line_number_table(LineNumberTable* table) {
        _line_number_table = table;
    }

    void set_name(string name) {
        _name = name;
    }

    void set_stack_map_table(StackMapTable* table) {
        _stack_map_table = table;
    }

public:
    short get_exception_table_length() {
        return _exception_table_length;
    }
    short  max_locals() {
        return _max_locals;
    }

};


#endif //XVM_CPP_CODEATTRIBUTE_H
