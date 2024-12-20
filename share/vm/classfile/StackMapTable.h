//
// Created by ziya on 2024/12/19.
//

#ifndef XVM_CPP_STACKMAPTABLE_H
#define XVM_CPP_STACKMAPTABLE_H


class StackMapTable {
private:
    int _attr_name_index;
    int _attr_length;
public:
    void set_attr_name_index(int index) {
        _attr_name_index = index;
    }

    void set_attr_length(int len) {
        _attr_length = len;
    }
};


#endif //XVM_CPP_STACKMAPTABLE_H
