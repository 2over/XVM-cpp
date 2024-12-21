//
// Created by ziya on 2024/12/20.
//

#ifndef XVM_CPP_CLASSFILESTREAM_H
#define XVM_CPP_CLASSFILESTREAM_H

#include "../../../include/common.h"

class ClassFileStream {
private:
    int _start;
    int _end;
    int _current;

    char *_source;
    string _class_name;
public:
    ClassFileStream(string class_name) {
        _start = 0;
        _end = 0;
        _current = 0;
        _class_name = class_name;
    }

public:
    char *container() {
        return _source;
    }

    void set_class_name(string class_name) {
        _class_name = class_name;
    }

    void create_container(int size) {
        _source = new char[size];
        _end = _start + size;
    }

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

public:
    byte get_u1();

    short get_u2();

    short get_u2_fast();

    int get_u4();

    long get_u8();

    void inc(int step);

    void copy(char *str, short len);

};


#endif //XVM_CPP_CLASSFILESTREAM_H
