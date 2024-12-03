//
// Created by xiehao on 2024/12/2.
//

#include "../common.h"
#include "../memory/memory_pool.h"

typedef enum {
    GC_STATUS_CLOSED,
    GC_STATUS_WORKING
} GC_Status;

class GCFactory {
private:
    GC_Status m_status;

public:
    static GCFactory *get_instance() {
        static GCFactory factory;
        return &factory;
    }

public:
    GC_Status get_status();

    GCFactory *set_status(GC_Status status);

public:
    void minor_run(GC_Type type, MemoryChunk *mem_chunk);

    void major_run(GC_Type type, MemoryChunk *mem_chunk);

    void full_run(GC_Type type, MemoryPool *mem_pool);
};
