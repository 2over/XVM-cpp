//
// Created by ziya on 2024/12/18.
//

#ifndef XVM_CPP_INSTANCEOOPDESC_H
#define XVM_CPP_INSTANCEOOPDESC_H

#include "oopDesc.h"
#include "../memory/Universe.h"
#include "Klass.h"
#include <map>

typedef class oopDesc *oop;
typedef class InstanceOopDesc *instanceOop;


class InstanceOopDesc : public OopDesc {
private:
    Klass *_klass;
    map<string, long> _fields;

public:
    InstanceOopDesc(Klass *klass) {
        _klass = klass;
    }

    Klass *klass() const {
        return _klass;
    }

    void *operator new(size_t size) {
        INFO_PRINT("从堆分配内存: %d\n", size);

        HeapWord *v = Universe::heap()->common_mem_allocate_init(size);
        return v->value();
    }

public:
    map<string, long> &fields() {
        return _fields;
    }

    long find(const string &class_name, const string &field_name) {
        string key = class_name + "#" + field_name;

        map<string, long>::iterator it = fields().find(key);
        if (it == fields().end()) {
            return 0;
        }

        return it->second;
    }

    void add_field(const string &class_name, const string &field_name, long v) {
        string key = class_name + "#" + field_name;
        fields().insert(pair<string, long>(key, v));
    }

};


#endif //XVM_CPP_INSTANCEOOPDESC_H
