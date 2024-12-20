//
// Created by ziya on 2024/12/19.
//

#ifndef XVM_CPP_LINENUMBERTABLE_H
#define XVM_CPP_LINENUMBERTABLE_H

#include "../../../include/common.h"

struct LineNumberItem {
    short start_pc;
    short line_number;
};

class LineNumberTable {
private:
    short _name_index;
    int _length;
    short _table_length;
    LineNumberItem *_table;

    string _name;
public:
    LineNumberTable() {}

    LineNumberTable(int size) {
        _length = size;


        /**
         * -2: 因为字节码文件中的length是算上了_table_length占用 的2B
         * 一个LineNumberItem只占用10B
         */
        _table = (LineNumberItem *) calloc(size - 2, 1);
    }

    LineNumberItem *table() const {
        return _table;
    }

public:
    void set_name_index(short v) {
        _name_index = v;
    }

    void set_table_length(short v) {
        _table_length = v;
    }

    void set_name(string s) {
        _name = s;
    }
};


#endif //XVM_CPP_LINENUMBERTABLE_H
