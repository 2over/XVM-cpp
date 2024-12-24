//
// Created by ziya on 2024/12/23.
//

#include "Metaspace.h"
#include "../../../include/memory/memory_pool.h"
#include "Metachunk.h"
#include "BlockFreelist.h"

extern MemoryPool g_mempool;

static ChunkIndex next_chunk_index(ChunkIndex i) {
    assert(i < NumberOfInUseLists, "Out of bound");
    return (ChunkIndex) (i + 1);
}

class SpaceManager {
    friend class Metaspace;

private:

    //该SpaceManager正在使用的块列表。分配
    //从当前块完成。该列表用于回收分配
    //当SpaceManager被释放时块

    // List of chunks in use by this SpaceManager. Allocations
    // are done from the current chunk. The list is used for deallocating
    // chunks when the SpaceManager is freed
    Metachunk *_chunks_in_use[NumberOfInUseLists];
    Metachunk *_current_chunk;

    //
    //每个空间管理器都有空闲的块列表
    //被假定为SpaceManager正在使用的块
    //所有正在被SpaceManager使用的块被释放
    //收集使用SpaceManager的类加载器

    // Free lists of blocks are per SpaceManager since they
    // are assumed to be in chunks in use by the SpaceManager
    // and all chunks in use by a SpaceManager are freed when
    // the class loader using the SpaceManager is collected
    BlockFreelist _block_freelists;

public:
    SpaceManager(Metaspace::MetadataType mdtype);

public:
    void initialize();

    BlockFreelist *block_freelists() const {
        return (BlockFreelist *) &_block_freelists;
    }

    MetaWord *allocate(size_t word_size);

    // Helper for allocation
    MetaWord *allocate_word(size_t word_size);

    //当前块分配失败时调用。
    //获取一个新的块（可能需要获取一个新的虚拟空间）；
    //并从该块中分配。

    // Called when an allocation from the current chunk fails
    // Gets a new chunk (may require getting a new virtual space),
    // and allocates from that chunk
    MetaWord *grow_and_allocate(size_t word_size);

    Metachunk *current_chunk() const {
        return _current_chunk;
    }

    void set_current_chunk(Metachunk *v) {
        _current_chunk = v;
    }
};

SpaceManager::SpaceManager(Metaspace::MetadataType mdtype) {
    initialize();
}

void SpaceManager::initialize() {
    for (ChunkIndex i = ZeroIndex; i < NumberOfInUseLists; i = next_chunk_index(i)) {
        _chunks_in_use[i] = NULL;
    }

    _current_chunk = NULL;
}

MetaWord *SpaceManager::allocate(size_t word_size) {
    BlockFreelist *fl = block_freelists();
    MetaWord *p = allocate_word(word_size);
    return p;
}

MetaWord *SpaceManager::allocate_word(size_t word_size) {
    MetaWord *result = NULL;
    if (current_chunk() != NULL) {
        result = current_chunk()->allocate(word_size);
    }

    if (NULL == result) {
        ERROR_PRINT("分配内存失败\n");
        exit(-1);

        // 后续优化,自动扩容
        // result = grow_and_allocate()
    }

    return result;
}

MetaWord *SpaceManager::grow_and_allocate(size_t word_size) {
    return NULL;
}

MetaWord *Metaspace::allocate(ClassLoaderData *loader_data, size_t word_size, bool read_only, MetaspaceObj::Type type) {
    MetadataType mdtype = (type == MetaspaceObj::ClassType) ? ClassType : NonClassType;

    MetaWord *result = loader_data->metaspace
}