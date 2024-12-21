//
// Created by ziya on 2024/12/20.
//

#ifndef XVM_CPP_CLASSPATHDIRENTRY_H
#define XVM_CPP_CLASSPATHDIRENTRY_H
#include "../../../include/common.h"
#include "ClassFileStream.h"

class ClassPathDirEntry {

private:
    // TODO target
    string _dir = "/target/classes";
    string _suffix = ".class";
};


#endif //XVM_CPP_CLASSPATHDIRENTRY_H
