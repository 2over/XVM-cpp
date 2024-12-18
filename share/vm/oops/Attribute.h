//
// Created by ziya on 2024/12/18.
//

#ifndef XVM_CPP_ATTRIBUTE_H
#define XVM_CPP_ATTRIBUTE_H


class Attribute {

private:
    short _name_index;
    int _length;

public:
    void set_name_index(short index) {
        _name_index = index;
    }

    void set_length(int len) {
        _length = len;
    }

};


#endif //XVM_CPP_ATTRIBUTE_H
