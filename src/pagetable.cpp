#include "pagetable.hpp"

PageTable::PageTable(Process *process, int pageSize, pair<bool *, int>memoryMap) {
    if (process == nullptr) {
        return;
    }

    m_process = process;
    m_memoryMap = memoryMap;
    setPageSize(pageSize);
    init();
}

PageTable::~PageTable() {
    if (m_table) {
        delete m_table;
    }
}

void PageTable::setPageSize(int pageSize) {
    if (pageSize < 128) {
        pageSize = 128;
    }
    m_pageSize = pageSize;
}

void PageTable::init() {
    int numberOfPagse = m_process->getSize() / m_pageSize;
    m_length = numberOfPagse + 1;
    m_table = new tableElement[m_length];

    if (m_memoryMap.second < 1 || m_memoryMap.first == nullptr) {
        return;
    }
    int index = 1;
    if (m_memoryMap.first) {
        for (int i = 1; i < m_memoryMap.second; i++) {
            if (!m_memoryMap.first[i]) {
                m_table[index].fNumber = i;
                m_table[index++].isValid = i;
                numberOfPagse--;
                if (!numberOfPagse) {
                    return;
                }
            }
        }
    }

    int frameIndex = 1;
    for (int i = index; i < m_length; i++) {
        frameIndex = frameIndex % m_memoryMap.second;
        if (frameIndex == 0) {
            frameIndex = 1;
        }

        m_table[i].fNumber = frameIndex++;
        m_table[i].isValid = true;
        numberOfPagse--;
        if (!numberOfPagse) {
            return;
        }
    }
}

PageTable::tableElement *PageTable::getTable() {
    return m_table;
}

int PageTable::getLength() {
    return m_length;
}

int PageTable::getProcessID() {
    return m_process->getID();
}
