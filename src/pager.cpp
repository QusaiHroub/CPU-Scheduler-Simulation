#include "pager.hpp"

Pager::Pager() {

}

Pager::Pager(int mem_size, int frame_size) {
    init(mem_size, frame_size);
}

Pager::~Pager() {
    if (m_memMap.first) {
        delete (m_memMap.first);
    }
}

void Pager::init(int memSize, int fSize) {
    m_memSize = memSize;
    m_fSize = fSize;
    m_memMap.second = m_memSize / m_fSize;
    if (m_memMap.first) {
        delete (m_memMap.first);
        m_memMap.first = nullptr;
    }
    m_memMap.first = (bool *) calloc(m_memMap.second, sizeof(bool));
}

pair<PageTable **, int> Pager::paging(Process * processes, int len) {
    PageTable **list = new PageTable*[len];
    for (int i = 0; i < len; i++) {
        list[i] = new PageTable(&processes[i], m_fSize, m_memMap);
    }

    return pair<PageTable **, int> (list, len);
}
