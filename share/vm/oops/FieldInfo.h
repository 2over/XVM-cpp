//
// Created by ziya on 2024/12/18.
//

#ifndef XVM_CPP_FIELDINFO_H
#define XVM_CPP_FIELDINFO_H

#include "../utilities/AccessFlags.h"
#include "Klass.h"

class FieldInfo {
private:
    Klass *_belong_klass;
    AccessFlags *_flags;
    short _name_index;
    short _descriptor_index;
    short _attributes_count;

    string _name;

public:
    FieldInfo(Klass *klass) {
        _belong_klass = klass;
    }

public:
    void set_belong_klass(Klass *klass) {
        _belong_klass = klass;
    }

    void set_flags(AccessFlags flags) {
        _flags = new AccessFlags(flags);
    }

    void set_name_index(short v) {
        _name_index = v;
    }

    void set_descriptor_index(short v) {
        _descriptor_index = v;
    }

    void set_attributes_count(short v) {
        _attributes_count = v;
    }

    void set_name(string name) {
        _name = name;
    }


};


#endif //XVM_CPP_FIELDINFO_H
