#include "pager.hpp"

Pager::Pager() {

}

Pager::Pager(int mem_size, int frame_size) {
    init(mem_size, frame_size);
}

Pager::~Pager() {
    if (m_memMap.first.first) {
        delete (m_memMap.first.first);
    }
    if (m_memMap.second) {
        delete m_memMap.second;
    }
}

void Pager::init(int memSize, int fSize) {
    m_memSize = memSize;
    m_fSize = fSize;
    m_memMap.first.second = m_memSize / m_fSize;
    if (m_memMap.first.first) {
        delete (m_memMap.first.first);
        m_memMap.first.first = nullptr;
    }
    m_memMap.first.first = (bool *) calloc(m_memMap.first.second, sizeof(bool));
    m_memMap.first.first[1] = true;
    m_memMap.first.first[2] = true;
    if (m_memMap.second) {
        delete m_memMap.second;
    }
    m_memMap.second = new pair<int, int>[m_memMap.first.second];
    for (int i = 0; i < m_memMap.first.second; i++) {
        m_memMap.second[i] = pair <int, int> (-1, -1);
    }
}

pair<PageTable **, int> Pager::paging(Process * processes, int len) {
    PageTable **list = new PageTable*[len];
    for (int i = 0; i < len; i++) {
        list[i] = new PageTable(&processes[i], m_fSize, m_memMap.first);
    }

    return pair<PageTable **, int> (list, len);
}

pair < pair < bool *, int >, pair< int, int > *> &Pager::getMemMap() {
    return m_memMap;
}
