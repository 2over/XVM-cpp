//
// Created by ziya on 2024/12/23.
//

#ifndef XVM_CPP_METASPACE_H
#define XVM_CPP_METASPACE_H

#include "../../../include/common.h"
#include "MetaspaceObj.h"

class ClassLoaderData;
class MetaspaceObj;
class SpaceManager;

class Metaspace {
    friend class SpaceManager;
public:
    enum MetadataType {
        ClassType,
        NonClassType,
        MetadataTypeCount
    };

    enum MetaspaceType {
        StandardMetaspaceType,
        BootMetaspaceType,
        ROMetaspaceType,
        ReadWriteMetaspaceType,
        AnonymousMetaspaceType,
        ReflectionMetaspaceType
    };

public:
    Metaspace(MetaspaceType type);
    ~Metaspace();

public:
    SpaceManager* _vsm;
    SpaceManager* vsm() const { return _vsm; }

    SpaceManager* _class_vsm;
    SpaceManager* class_vsm() const { return _class_vsm; }


public:
    void initialize(MetaspaceType type);

    static MetaWord* allocate(ClassLoaderData* loader_data, size_t word_size, bool read_only, MetaspaceObj::Type type);

    // Allocate space for metadata of type mdtype. This is space
    // within a Metachunk and is used by allocate(ClassLoaderData* , size_t ,bool, MetdataType, TRAPS)
    MetaWord* allocate(size_t word_size, MetadataType mdtype);


};


#endif //XVM_CPP_METASPACE_H
