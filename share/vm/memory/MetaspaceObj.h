//
// Created by xiehao on 2024/12/13.
//

#ifndef XVM_CPP_METASPACEOBJ_H
#define XVM_CPP_METASPACEOBJ_H


#include "../../../include/common.h"
#include "../../../share/vm/memory/Universe.h"

#define METASPACE_OBJ_TYPES_DO(f) \
    f(Unknown) \
    f(Class) \
    f(Symbol) \
    f(TypeArrayU1) \
    f(TypeArrayU2) \
    f(TypeArrayU4) \
    f(TypeArrayU8) \
    f(TypeArrayOther) \
    f(Method) \
    f(ConstMethod) \
    f(MethodData) \
    f(ConstantPool) \
    f(ConstantPoolCache) \
    f(Annotation) \
    f(MethodCounters) \
    f(Deallocated)

#define METASPACE_OBJ_TYPE_DECLARE(name) name ## Type,
#define METASPACE_OBJ_TYPE_NAME_CASE(name) case name ## Type: return #name;

class MetaspaceObj {
public:
    enum Type {
        // Types are MetaspaceObj::ClassType, MetaspaceObj::SymbolType, etc
        METASPACE_OBJ_TYPES_DO(METASPACE_OBJ_TYPE_DECLARE)
        _number_of_types
    };


public:
    void *operator new(size_t size) {
        INFO_PRINT("从元空间分配内存: %d\d", size);
        HeapWord *v = Universe::heap()->common_mem_allocate_init(size);

        return v->value();
    }
};


#endif //XVM_CPP_METASPACEOBJ_H
