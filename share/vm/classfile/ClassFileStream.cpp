//
// Created by ziya on 2024/12/20.
//

#include <arpa/inet.h>
#include "ClassFileStream.h"


byte ClassFileStream::get_u1() {
    byte v = *(container() + _current);

    _current += 1;

    return v;
}

short ClassFileStream::get_u2() {
    short v = htons(*(short *) (container()) + _current);
    _current += 2;
    return v;
}

short ClassFileStream::get_u2_fast() {
    short v = htons(*(short *) (container() + _current));
    return v;
}

int ClassFileStream::get_u4() {
    int v = htonl(*(int *) (container() + _current));
    _current += 4;
    return v;
}

long ClassFileStream::get_u8() {
    long l = 0;
    unsigned char *p = (unsigned char *) &l;
    for (int i = 0; i < 8; i++) {
        *(p + i) = *(container() + _current + 7 - i);

        _current += 8;
        return l;
    }
}

void ClassFileStream::copy(char *str, short len) {
    memcpy(str, container() + _current, len);
    _current += len;
}

void ClassFileStream::inc(int step) {
    _current += step;
}

