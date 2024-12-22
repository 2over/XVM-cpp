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

public:
    ClassFileStream *open_stream(string class_name);

    ClassFileStream *open_file_stream(string path, string clas_name);

    string &replace_all(string &str, const string &old_value, const string &new_value) {
        while (true) {
            string::size_type pos(0);
            if ((pos = str.find(old_value)) != string::npos) {
                str.replace(pos, old_value.length(), new_value);
            } else {
                break;
            }
        }

        return str;
    }
};


#endif //XVM_CPP_CLASSPATHDIRENTRY_H
