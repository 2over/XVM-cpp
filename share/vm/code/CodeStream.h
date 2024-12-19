//
// Created by ziya on 2024/12/19.
//

#ifndef XVM_CPP_CODESTREAM_H
#define XVM_CPP_CODESTREAM_H


class CodeStream {
private:
    int     _size;
    char*   _codes;
    int     _current;

public:
    CodeStream(int size) {
        _size = size;
        _current = 0;

        _codes = new char[size];
    }

    char* codes() const {
        return _codes;
    }

    bool end() {
        return _current == _size;
    }

    void reset() {
        _current = 0;
    }

public:
    char get_u1();

    char get_u1_fast();

    short get_u2();

    short get_u2_fast();

    int get_u4();

    long get_u8();

    void inc(int step);

    void dec(int step);

    void copy(char *str, short len);

};


#endif //XVM_CPP_CODESTREAM_H
