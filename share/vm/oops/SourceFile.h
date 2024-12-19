//
// Created by ziya on 2024/12/18.
//

#ifndef XVM_CPP_SOURCEFILE_H
#define XVM_CPP_SOURCEFILE_H


class SourceFile {

private:
    short   _name_index;
    int     _length;
    short   _sourcefile_index;

public:
    void set_name_index(int v) {
        _name_index = v;
    }

    void set_length(int length) {
        _length = length;
    }

    void set_sourcefile_index(int index) {
        _sourcefile_index = index;
    }
};


#endif //XVM_CPP_SOURCEFILE_H
