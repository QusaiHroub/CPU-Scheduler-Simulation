/*
 * This file is part of OS Project.
 *
 * Authors
 * Qusai Hroub
 *
 */

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

//deconstructor
PageTable::~PageTable() {
    if (m_table) {
        delete m_table;
    }
}

//This function receives one Parameter to change page size (frame size).
void PageTable::setPageSize(int pageSize) {
    
    //check page size if less than 128
    if (pageSize < 128) {
        pageSize = 128;
    }
    m_pageSize = pageSize;
}

//To implements PagerTable
void PageTable::init() {
    int numberOfPagse = m_process->getSize() / m_pageSize;
    m_length = numberOfPagse + 1;
    if (m_process->getSize() % m_pageSize) {
        m_length++;
        numberOfPagse++;
    }

    m_table = new tableElement[m_length];

    if (m_memoryMap.second < 1 || m_memoryMap.first == nullptr) {
        return;
    }

    //search about not used frames and make the process use them.
    int index = 1;
    if (m_memoryMap.first) {
        for (int i = 3; i < m_memoryMap.second; i++) {
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

    //if not all pages are pointed on their own frame, start from the first allocatable frame and select them incrementally.
    //may be the same frame pointed by more than one page.
    int frameIndex = 3;
    for (int i = index; i < m_length; i++) {
        frameIndex = frameIndex % m_memoryMap.second;
        if (frameIndex == 0) {
            frameIndex = 3;
        }

        m_table[i].fNumber = frameIndex++;
        m_table[i].isValid = true;
        numberOfPagse--;
        if (!numberOfPagse) {
            return;
        }
    }
}

/*
    This function return  array <m_table> of type tableElement. 
    tableElement is <struct> .
*/
PageTable::tableElement *PageTable::getTable() {
    return m_table;
}

//To return length 
int PageTable::getLength() {
    return m_length;
}

//To return Process id 
int PageTable::getProcessID() {
    return m_process->getID();
}
