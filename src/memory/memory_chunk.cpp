//
// Created by xiehao on 2024/12/3.
//

#include "../../include/common.h"
#include "../../include/memory/memory_chunk.h"
#include "../../include/gc/gc_factory.h"

MemoryChunk::MemoryChunk(uint size, char *filename, uint line) : m_size(size), m_filename(filename), m_line(line) {
    m_align_size = ALIGN_SIZE;
    m_cell_num = ((size - 1) / m_align_size) + 1;
    m_size = m_cell_num * m_align_size;

    this->m_data = calloc(m_size, sizeof(byte));

    if (NULL == this->m_data) {
        ERROR_PRINT("分配内存失败\n");
        exit(1);
    }

    switch (DEFAULT_GC_TYPE) {
        case GC_MARK_CLEAN:
        case GC_MARK_COLLECT:
            m_used_cell_num = 0;
            m_available_table.push_front(new MemoryCell(0, m_cell_num));
            break;
        case GC_MARK_COPY:
            m_used_cell_num = 0;
            m_cell_start = 0;

            m_available_table.push_front(new MemoryCell(0, m_cell_num / 2));
            m_idle_table.push_front(new MemoryCell(m_cell_num / 2, m_cell_num / 2));
            break;
    }
}