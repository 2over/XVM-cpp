//
// Created by ziya on 2024/12/19.
//

#include <arpa/inet.h>
#include "CodeStream.h"
#include "../../../include/common.h"

char CodeStream::get_u1() {
    char v = *(codes() + _current);

    _current += 1;
    return v;
}

char CodeStream::get_u1_fast() {
    char v = *(codes() + _current);
    return v;
}

short CodeStream::get_u2() {
    short v = htons(*(short *) (codes() + _current));
    _current += 2;
    return v;
}

short CodeStream::get_u2_fast() {
    short v = htons(*(short *) (codes() + _current));
    return v;
}

int CodeStream::get_u4() {
    int v = htonl(*(int *) (codes() + _current));
    _current += 4;
    return v;
}

long CodeStream::get_u8() {
    long l = 0;
    unsigned char *p = (unsigned char *) &l;
    for (int i = 0; i < 8; ++i) {
        *(p + i) = *(codes() + _current + 7 - i);
    }

    _current += 8;
    return l;
}

void CodeStream::inc(int step) {
    _current += step;
}

void CodeStream::dec(int step) {
    _current -= step;
}

void CodeStream::copy(char *str, short len) {
    memcpy(str, codes() +_current, len);
    _current += len;
}