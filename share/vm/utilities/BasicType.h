//
// Created by ziya on 2024/12/16.
//

#ifndef XVM_CPP_BASICTYPE_H
#define XVM_CPP_BASICTYPE_H

#define ACC_PUBLIC              0x0001 //class, field, method
#define ACC_PRIVATE             0x0002 // class, field, method
#define ACC_PROTECTED           0x0004 // class, field, method
#define ACC_STATIC              0x0008 // field, method
#define ACC_FINAL               0x0010 // class, field, method
#define ACC_SUPER               0x0020 // class
#define ACC_SYNCHRONIZED        0x0020 // method
#define ACC_VOLATILE            0x0040 // field
#define ACC_BRIDGE              0x0040 // method
#define ACC_VARARGS             0x0080 // method
#define ACC_TRANSIENT           0x0080 // field
#define ACC_NATIVE              0x0100 // method
#define ACC_INTERFACE           0x0200 // class
#define ACC_ABSTRACT            0x0400 // class, method
#define ACC_STRICT              0x0800 // method
#define ACC_SYNTHETIC           0x1000 // class, field, method
#define ACC_ANNOTATION          0x2000 // class
#define ACC_ENUM                0x4000 // class(?) field inner

#define JVM_SIGNATURE_ARRAY     '['
#define JVM_SIGNATURE_BYTE      'B'
#define JVM_SIGNATURE_CHAR      'C'
#define JVM_SIGNATURE_CLASS     'L'
#define JVM_SIGNATURE_ENDCLASS  ';'
#define JVM_SIGNATURE_ENUM      'E'
#define JVM_SIGNATURE_FLOAT     'F'
#define JVM_SIGNATURE_DOUBLE    'D'
#define JVM_SIGNATURE_FUNC      '('
#define JVM_SIGNATURE_ENDFUNC   ')'
#define JVM_SIGNATURE_INT       'I'
#define JVM_SIGNATURE_LONG      'J'
#define JVM_SIGNATURE_SHORT     'S'
#define JVM_SIGNATURE_VOID      'V'
#define JVM_SIGNATURE_BOOLEAN   'Z'

// Constant Pool Entries
enum {
    JVM_CONSTANT_Utf8                   = 1,
    JVM_CONSTANT_Unicode                = 2, // unused
    JVM_CONSTANT_Integer                = 3,
    JVM_CONSTANT_Float                  = 4,
    JVM_CONSTANT_Long                   = 5,
    JVM_CONSTANT_Double                 = 6,
    JVM_CONSTANT_Class                  = 7,
    JVM_CONSTANT_String                 = 8,
    JVM_CONSTANT_Fieldref               = 9,
    JVM_CONSTANT_Methodref              = 10,
    JVM_CONSTANT_InterfaceMethodref     = 11,
    JVM_CONSTANT_NameAndType            = 12,
    JVM_CONSATANT_MetodHandle           = 15, // JSR 292
    JVM_CONSTANT_MethodType             = 16, // JSR 292
    JVM_CONSTANT_InvokeDynamic          = 18
};
class BasicType {

};


#endif //XVM_CPP_BASICTYPE_H
