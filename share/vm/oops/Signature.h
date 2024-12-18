//
// Created by ziya on 2024/12/18.
//

#ifndef XVM_CPP_SIGNATURE_H
#define XVM_CPP_SIGNATURE_H
#include "Attribute.h"

class Signature : public Attribute {
private:
    short _signature_index;

public:
    void set_signature_index(short index) {
        _signature_index = index;
    }
};


#endif //XVM_CPP_SIGNATURE_H
