//
// Created by ziya on 2024/12/21.
//

#ifndef XVM_CPP_CLASSFILEPARSER_H
#define XVM_CPP_CLASSFILEPARSER_H


#include "ClassFileStream.h"
#include "../oops/InstanceKlass.h"

class ClassFileParser {
private:
    ClassFileStream *_stream;

public:
    ClassFileStream *stream() const {
        return _stream;
    }

    ClassFileParser(ClassFileStream *stream);

    InstanceKlass *parseClassFile();

    void parseConstantPool(InstanceKlass *klass);

    void parseFields(InstanceKlass *klass);

    void parseMethods(InstanceKlass *klass);

    void parseCodeAttribute(MethodInfo *method);

    void parseLocalVariableTable(MethodInfo *method);

    void parseLineNumberTable(MethodInfo *method);

    void parseClassAttribute(InstanceKlass *klass);

    void parseExceptionTable(MethodInfo *method);

    void parseStackMapTable(MethodInfo *method);

    void parseExceptions(MethodInfo *method);

    void parseSignature(MethodInfo *method);

    void parseDeprecated(MethodInfo *method);

    void parseRuntimeVisibleAnnotations(MethodInfo *method);

    void parseInnerClasses(InstanceKlass *klass);


};


#endif //XVM_CPP_CLASSFILEPARSER_H
