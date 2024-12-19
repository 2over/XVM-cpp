//
// Created by ziya on 2024/12/18.
//

#ifndef XVM_CPP_INNERCLASSES_H
#define XVM_CPP_INNERCLASSES_H

#include "../../../include/common.h"
#include "Attribute.h"

struct InnerClass {
    short inner_class_info_index;
    short outer_class_info_index;
    short inner_name_index;
    short inner_class_access_flags;
};

class InnerClasses : public Attribute {

private:
    short _num_of_classes;
    InnerClass *_classes;

public:
    ~InnerClasses() {
        if (NULL != _classes) {
            delete[] _classes;
        }
    }

public:
    void set_num_of_classes(short num) {
        _num_of_classes = num;
    }

    void create_classes_table() {
        _classes = new InnerClass[_num_of_classes];
    }
};


#endif //XVM_CPP_INNERCLASSES_H
