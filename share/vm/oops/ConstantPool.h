//
// Created by ziya on 2024/12/17.
//

#ifndef XVM_CPP_CONSTANTPOOL_H
#define XVM_CPP_CONSTANTPOOL_H

#include "Klass.h"

class ConstantPool {

private:
    Klass *_belong_klass;
    short _size;
    char *_tags;

    /**
     * key: 常量池的index
     * val: 统一用long 存储
     * 1. 指针
     * 2. 基本类型
     */
    long *_container;

public:
    ConstantPool() {}

    ConstantPool(short size) {
        _size = size;
        _tags = new char[size];
        _container = new long[size];

        // 现实中,这个位置是没用的
        _tags[0] = 0;
        _container[0] = 0;
    }

    void set_belong_klass(Klass *klass) {
        _belong_klass = klass;
    }

    void set_size(short v) {
        _size = v;
    }

    long *container() const {
        return _container;
    }

public:
    void add_item(short index, char tag, int val) {
        _tags[index] = tag;
        _container[index] = val;
    }

    void add_item(short index, char tag, char *str) {
        _tags[index] = tag;
        _container[index] = reinterpret_cast<long>(new string(str));
    }

public:
    string &get_item_string(short index);

    string *get_item_string2(short index);

    int get_item_int(short index);

    string &get_class_name_from_fieldref(int index);

    string &get_field_name_from_fieldref(int index);

    string &get_field_descriptor_from_fieldref(int index);

    string &get_class_name_from_methodref(int index);

    string &get_method_name_from_methodref(int index);

    string &get_method_descriptor_from_methodref(int index);

    string &get_super_class_name(int super_class_index);

    string &get_class_name(int class_index);
};


#endif //XVM_CPP_CONSTANTPOOL_H
