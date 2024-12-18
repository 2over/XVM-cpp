//
// Created by ziya on 2024/12/16.
//

#ifndef XVM_CPP_ACCESSFLAGS_H
#define XVM_CPP_ACCESSFLAGS_H
#include "BasicType.h"

class AccessFlags {

private:
    int _flags;
public:
    AccessFlags() {}
    AccessFlags(int flags) {
        _flags = flags;
    }

public:
    // Java access flags
    bool is_public      () const        { return (_flags & JVM_ACC_PUBLIC       ) != 0; }
    bool is_private     () const        { return (_flags & JVM_ACC_PRIVATE      ) != 0; }
    bool is_protected   () const        { return (_flags & JVM_ACC_PROTECTED    ) != 0; }
    bool is_static      () const        { return (_flags & JVM_ACC_STATIC       ) != 0; }
    bool is_final       () const        { return (_flags & JVM_ACC_FINAL        ) != 0; }
    bool is_synchronized() const        { return (_flags & JVM_ACC_SYNCHRONIZED ) != 0; }
    bool is_super       () const        { return (_flags & JVM_ACC_SUPER        ) != 0; }
    bool is_volatile    () const        { return (_flags & JVM_ACC_VOLATILE     ) != 0; }
    bool is_transient   () const        { return (_flags & JVM_ACC_TRANSIENT    ) != 0; }
    bool is_native      () const        { return (_flags & JVM_ACC_NATIVE       ) != 0; }
    bool is_interface   () const        { return (_flags & JVM_ACC_INTERFACE    ) != 0; }
    bool is_abstract    () const        { return (_flags & JVM_ACC_ABSTRACT     ) != 0; }
    bool is_strict      () const        { return (_flags & JVM_ACC_STRICT       ) != 0; }

};


#endif //XVM_CPP_ACCESSFLAGS_H
