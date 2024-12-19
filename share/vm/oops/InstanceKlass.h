//
// Created by ziya on 2024/12/16.
//

#ifndef XVM_CPP_INSTANCEKLASS_H
#define XVM_CPP_INSTANCEKLASS_H
#include "Klass.h"
#include "instanceOopDesc.h"
#include "../../../include/common.h"
#include "../utilities/AccessFlags.h"
#include "ConstantPool.h"
#include "FieldInfo.h"
#include "MethodInfo.h"
#include "SourceFile.h"
#include "InnerClasses.h"


class InstanceKlass : public Klass {
private:
    int _magic;
    short _minor_version;
    short _major_version;

    short _constant_pool_count;
    ConstantPool* _constant_pool;

    AccessFlags* _access_flags;

    short _this_class;
    Klass* _this_klass;

    short _super_class;
     Klass* _super_klass;

     short _interfaces_count;
     vector<Klass *> _interfaces;

     short _fields_count;
     vector<FieldInfo *> _fields;

     short _methods_count;
     vector<MethodInfo *> _methods;

     vector<MethodInfo *> _vtable;
     vector<MethodInfo *> _itable;

     // 方法对应的属性个数(属性是分开存储的: Code Exception)
     short _attributes_count;

     SourceFile* _source_file;
     InnerClasses* _inner_classes;

     char _init_state;
     string _name;
public:
    instanceOop allocate_instance(size_t size);

    // See "The Java Virtual Machine Specification" section 2.16.2-5 for a detailed description
    // of the class loading & initialization procedure, and the use of the states.
    enum ClassState {
        allocated,              // allocated (but not yet linked)
        loaded,                 // loaded and inserted in class hierarchy (but not linked yet)
        linked,                 // successfully linked/verified (but not initialized yet)
        being_initialized,      // currently running class initializer
        fully_initialized,      // initialized (successfull final state)
        initialization_error,   // error happened during initialization
    };

public:
    InstanceKlass() {
        _init_state = loaded;
        _super_klass = NULL;
    }

    ConstantPool* constant_pool() {
        return _constant_pool;
    }

    vector<MethodInfo *> & methods() {
        return _methods;
    }

    vector<MethodInfo *> vtable() {
        return _vtable;
    }

    vector<MethodInfo *> itable() {
        return _itable;
    }

    string& name() {
        return _name;
    }

public:
    bool should_be_intialized() const {
        return !is_initialized();
    }

    bool is_initialized() const {
        return _init_state == fully_initialized;
    }

    void initalize();

    void initialize_impl();

    void link_class();

    void link_class_impl(InstanceKlass* klass);

public:
    // initialization state
    bool is_loaded() const              { return _init_state >= loaded; }
    bool is_linked() const              { return _init_state >= linked; }
    bool is_not_initialized() const     { return _init_state < being_initialized; }
    bool is_being_initialized() const   { return _init_state == being_initialized; }
    bool is_in_error_state() const      { return _init_state == initialization_error; }

public:
    void set_magic(int v) {
        _magic = v;
    }

    void set_minor_version(short v) {
        _major_version = v;
    }

    void set_constant_pool_count(short v) {
        _constant_pool_count = v;
    }

    void set_constant_pool(ConstantPool* pool) {
        _constant_pool = pool;
    }

    void set_access_flags(short flags) {
        _access_flags = new AccessFlags(flags);
    }

    void set_this_class(short v) {
        _this_class = v;
    }

    void set_this_klass(Klass* klass) {
        _this_klass = klass;
    }

    void set_super_class(short v) {
        _super_class = v;
    }

    void set_super_klass(Klass* klass) {
        _super_klass = klass;
    }

    void set_interface_count(short v) {
        _interfaces_count = v;
    }


};


#endif //XVM_CPP_INSTANCEKLASS_H
