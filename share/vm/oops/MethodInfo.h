//
// Created by xiehao on 2024/12/3.
//

#ifndef XVM_CPP_METHODINFO_H
#define XVM_CPP_METHODINFO_H

#include "Klass.h"
#include "../utilities/AccessFlags.h"
#include "Attribute.h"
#include "Exceptions.h"
#include "Signature.h"
#include "Deprecated.h"
#include "RuntimeVisibleAnnotations.h"

class MethodInfo {
private:
    Klass *_belong_klass;
    AccessFlags *_flags;

    short _name_index;
    short _descriptor_index;
    short _attributes_count;

    Attribute *_code_attribute;
    Exceptions *_exceptions;
    Signature *_signature;
    Deprecated *_deprecated;
    RuntimeVisibleAnnotations *_runtime_visible_annotations;

    string _name;
    string _descriptor;
    string _class_name;

public:
    MethodInfo() {}

    MethodInfo(Klass *klass) {
        _belong_klass = klass;
    }

    ~MethodInfo() {
        if (NULL != _flags) {
            delete _flags;
        }

        if (NULL != _code_attribute) {
            delete _code_attribute;
        }

        if (NULL != _exceptions) {
            delete _exceptions;
        }

        if (NULL != _signature) {
            delete _signature;
        }

        if (NULL != _deprecated) {
            delete _deprecated;
        }
    }

    Klass *klass() const {
        return _belong_klass;
    }

    Attribute *attribute() const {
        return _code_attribute;
    }

    string &name() {
        return _name;
    }

    string &descriptor() {
        return _descriptor;
    }

    string &class_name() {
        return _class_name;
    }

    AccessFlags *flags() const {
        return _flags;
    }

public:
    void set_belong_klass(Klass *klass) {
        _belong_klass = klass;
    }

    void set_flags(short flags) {
        _flags = new AccessFlags(flags);
    }

    void set_name_index(short v) {
        _name_index = v;
    }

    void set_descriptor_index(short v) {
        _descriptor_index = v;
    }

    void set_attributes_count(short v) {
        _attributes_count = v;
    }

    void set_code_attribute(Attribute *attr) {
        _code_attribute = attr;
    }

    void set_name(string name) {
        _name = name;
    }

    void set_class_name(string name) {
        _class_name = name;
    }

    void set_descriptor(string descriptor) {
        _descriptor = descriptor;
    }

    void set_exceptions(Exceptions *ex) {
        _exceptions = ex;
    }

    void set_signature(Signature *signature) {
        _signature = signature;
    }

    void set_deprecated(Deprecated *deprecated) {
        _deprecated = deprecated;
    }

    void set_runtime_visible_annotations(RuntimeVisibleAnnotations *annotations) {
        _runtime_visible_annotations = annotations;
    }

};


#endif //XVM_CPP_METHODINFO_H
