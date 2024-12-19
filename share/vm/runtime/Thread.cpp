//
// Created by xiehao on 2024/12/19.
//

#include "Thread.h"

void Thread::initialize_class(string class_name) {

}

void Thread::initialize_class(InstanceKlass *klass) {
    klass->initialize();
}