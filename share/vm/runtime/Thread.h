//
// Created by xiehao on 2024/12/19.
//

#ifndef XVM_CPP_THREAD_H
#define XVM_CPP_THREAD_H


#include "../utilities/ThreadShadow.h"
#include "../oops/InstanceKlass.h"

class Thread : public ThreadShadow{
public:
    static void initialize_class(string class_name);
    static void initialize_class(InstanceKlass* klass);

};


#endif //XVM_CPP_THREAD_H
