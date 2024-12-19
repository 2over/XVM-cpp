//
// Created by xiehao on 2024/12/19.
//

#ifndef XVM_CPP_STACKVALUE_H
#define XVM_CPP_STACKVALUE_H

#include "jni.h"
#include "../utilities/BasicType.h"

class StackValue {
private:
    BasicType _type;
    char _data[8];

public:
    StackValue(BasicType type, char v) {
        _type = type;
        *_data = v;
    }

    StackValue(BasicType type, long v) {
        _type = type;
        *(jlong *) _data = v;
    }

    StackValue(BasicType type, jobject v) {
        _type = type;
        *(jlong *) _data = (jlong) v;
    }

    jlong data() {
        return *(jlong *) _data;
    }
};


#endif //XVM_CPP_STACKVALUE_H
