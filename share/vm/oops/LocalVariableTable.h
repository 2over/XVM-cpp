//
// Created by ziya on 2024/12/19.
//

#ifndef XVM_CPP_LOCALVARIABLETABLE_H
#define XVM_CPP_LOCALVARIABLETABLE_H

#include "../../../include/common.h"

struct LocalVariableItem {
    short start_pc;
    short length;
    short name_index;
    short descriptor_index;
    short index;
};

class LocalVariableTable {
private:
    short _name_index;
    int _length;
    short _table_length;

    /**
     *  可以像数组一样访问
     *  | LocalVariableItem | LocalVariableItem | .... |
     */

    LocalVariableItem *_table;
public:
    LocalVariableTable() {}

    LocalVariableTable(int size) {
        _length = size;

        /**
         * -2 : 因为字节码文件中的length是算上了_table_length占用的2B
         * 一个LocalVariableItem 只占用10B
         */

        _table = static_cast<LocalVariableItem *>(calloc(size - 2, 1));
    }


    LocalVariableItem *table() const {
        return _table;
    }

public:
    void set_name_index(short v) {
        _name_index = v;
    }

    void set_table_length(int v) {
        _table_length = v;
    }
};


#endif //XVM_CPP_LOCALVARIABLETABLE_H
