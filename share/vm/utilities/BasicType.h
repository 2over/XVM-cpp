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
enum BasicType {
    T_BOOLEAN       = 4,
    T_CHAR          = 5,
    T_FLOAT         = 6,
    T_DOUBLE        = 7,
    T_BYTE          = 8,
    T_SHORT         = 9,
    T_INT           = 10,
    T_LONG          = 11,
    T_OBJECT        = 12,
    T_ARRAY         = 13,
    T_VOID          = 14,
    T_ADDRESS       = 15,
    T_NARROWOOP     = 16,
    T_METADATA      = 17,
    T_NARROWKLASS   = 18,
    T_CONFLICT      = 19, // for stack value type with conflicting contents
    T_ILLEGAL       = 99
};

// Flags
enum {
    JVM_ACC_PUBLIC          = 0x0001,
    JVM_ACC_PRIVATE         = 0x0002,
    JVM_ACC_PROTECTED       = 0x0004,
    JVM_ACC_STATIC          = 0x0008,
    JVM_ACC_FINAL           = 0x0010,
    JVM_ACC_SYNCHRONIZED    = 0x0020,
    JVM_ACC_SUPER           = 0x0020,
    JVM_ACC_VOLATILE        = 0x0040,
    JVM_ACC_BRIDGE          = 0x0080,
    JVM_ACC_TRANSIENT       = 0x0080,
    JVM_ACC_VARARGS         = 0x0080,
    JVM_ACC_NATIVE          = 0x0100,
    JVM_ACC_INTERFACE       = 0x0200,
    JVM_ACC_ABSTRACT        = 0x0400,
    JVM_ACC_STRICT          = 0x0800,
    JVM_ACC_SYNTHETIC       = 0x1000,
    JVM_ACC_ANNOTATION      = 0x2000,
    JVM_ACC_ENUM            = 0x4000
};

enum Bytecode {
    _illegal                = -1,

    // Java bytecodes
    _nop                    = 0, //0x00
    _aconst_null            = 1, // 0x01
    _iconst_m1              = 2, // 0x02
    _iconst_0               = 3, // 0x03
    _iconst_1               = 4, // 0x04
    _iconst_2               = 5, // 0x05
    _iconst_3               = 6, // 0x06
    _iconst_4               = 7, // 0x07
    _iconst_5               = 8, // 0x08
    _lconst_0               = 9, // 0x09
    _lconst_1               = 10, // 0x0a
    _fconst_0               = 11, // 0x0b
    _fconst_1               = 12, // 0x0c
    _fconst_2               = 13, // 0x0d
    _dconst_0               = 14, // 0x0e
    _dconst_1               = 15, // 0x0f
    _bipush                 = 16, // 0x10
    _sipush                 = 17, // 0x11
    _ldc                    = 18, // 0x12
    _ldc_w                  = 19, // 0x13
    _ldc2_w                 = 20, // 0x14
    _iload                  = 21 , // 0x15
    _lload                  = 22, // 0x16
    _fload                  = 23, // 0x17
    _dload                  = 24, // 0x18
    _aload                  = 25, // 0x19
    _iload_0                = 26, // 0x1a
    _iload_1                = 27, // 0x1b
    _iload_2                = 28, // 0x1c
    _iload_3                = 29, // 0x1d
    _lload_0                = 30, // 0x1e
    _lload_1                = 31, // 0x1f
    _lload_2                = 32, // 0x20
    _lload_3                = 33, // 0x21
    _fload_0                = 34, // 0x22
    _fload_1                = 35, // 0x23
    _fload_2                = 36, // 0x24
    _fload_3                = 37, // 0x25
    _dload_0                = 38, // 0x26
    _dload_1                = 39, // 0x27
    _dload_2                = 40, // 0x28
    _dload_3                = 41, // 0x29
    _aload_0                = 42, // 0x2a
    _aload_1                = 43, // 0x2b
    _aload_2                = 44, // 0x2c
    _aload_3                = 45, // 0x2d
    _iaload                 = 46, // 0x2e
    _laload                 = 47, // 0x2f
    _faload                 = 48, // 0x30
    _daload                 = 49, // 0x31
    _aaload                 = 50, // 0x32
    _baload                 = 51, // 0x33
    _caload                 = 52, // 0x34
    _saload                 = 53, // 0x35
    _istore                 = 54, // 0x36
    _lstore                 = 55, // 0x37
    _fstore                 = 56, // 0x38
    _dstore                 = 57, // 0x39
    _astore                 = 58, // 0x3a
    _istore_0               = 59, // 0x3b
    _istore_1               = 60, // 0x3c
    _istore_2               = 61, // 0x3d
    _istore_3               = 62, // 0x3e
    _lstore_0               = 63, // 0x3f
    _lstore_1               = 64, // 0x40
    _lstore_2               = 65, // 0x41
    _lstore_3               = 66, // 0x42
    _fstore_0               = 67, // 0x43
    _fstore_1               = 68, // 0x44
    _fsotre_2               = 69, // 0x45
    _fstore_3               = 70, // 0x46
    _dstore_0               = 71, // 0x47
    _dstore_1               = 72, // 0x48
    _dstore_2               = 73, // 0x49
    _dstore_3               = 74, // 0x4a
    _astore_0               = 75, // 0x4b
    _astore_1               = 76, // 0x4c
    _astore_2               = 77, // 0x4d
    _astore_3               = 78, // 0x4e
    _iastore                = 79, // 0x4f
    _lastore                = 80, // 0x50
    _fastore                = 81, // 0x51
    _dastore                = 82, // 0x52
    _aastore                = 83, // 0x53
    _bastore                = 84, // 0x54
    _castore                = 85, // 0x55
    _sastore                = 86, // 0x56
    _pop                    = 87, // 0x57
    _pop2                   = 88, // 0x58
    _dup                    = 89, // 0x59
    _dup_x1                 = 90, // 0x5a
    _dup_x2                 = 91, // 0x5b
    _dup2                   = 92, // 0x5c
    _dup2_x1                = 93, // 0x5d
    _dup2_x2                = 94, // 0x5e
    _swap                   = 95, // 0x5f
    _iadd                   = 96, // 0x60
    _ladd                   = 97, // 0x61
    _fadd                   = 98, // 0x62
    _dadd                   = 99, // 0x63
    _isub                   = 100, // 0x64

};

#endif //XVM_CPP_BASICTYPE_H
