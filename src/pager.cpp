/*
 * This file is part of OS Project.
 *
 * Authors
 * Qusai Hroub
 * Mohammad Abureesh
 *
 * memory paging simulation manager
 *
 */

#include "pager.hpp"

#include <vector>

//Default constructor.
Pager::Pager() {

}


/*
    This Constructors receives two parameters, the memory size and
    Frame size(Page size).
    call function init() and pass the memory size and frame size to it.
*/
Pager::Pager(Process *processes, int len, int mem_size, int frame_size) {
    init(processes, len, mem_size, frame_size);
}


//Deconstructors
Pager::~Pager() {
    if (m_memMap.first.first) {
        delete (m_memMap.first.first);
    }
    if (m_memMap.second) {
        delete m_memMap.second;
    }
}

//To initialization paging techne
void Pager::init(Process *processes, int len, int memSize, int fSize) {
    m_processes = processes;
    if (processes != nullptr) {
        for (int i = 0; i < len; i++) {
            m_processMap[processes[i].getID()] = i;
        }
    }
    m_memSize = memSize;
    m_fSize = fSize;
    m_memMap.first.second = m_memSize / m_fSize;
    if (m_memMap.first.first) {
        delete (m_memMap.first.first);
        m_memMap.first.first = nullptr;
    }

    //init memory map
    //frame 0 is null frame
    //frames 1, 2 are used by OS and no process can allocate them.
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

//Returns the pair that contains memory map Pointers
pair < pair < bool *, int >, pair< int, int > *> &Pager::getMemMap() {
    return m_memMap;
}

//map logical address to physical address.
Pager::Address Pager::mapping(Process  &process, int logicalAddress) {
    PageTable *table = process.getPageTable();
    Address address;
    if (!table) {
        address.errorCode = 1;
        return address;
    }

    address.logicalAndPhysicalAddress.first = logicalAddress;
    address.pd.first = address.logicalAndPhysicalAddress.first / m_fSize;
    address.pd.second = address.logicalAndPhysicalAddress.first - address.pd.first * m_fSize;
    address.pd.first++;

    //check if the logical address is valid address to process with id (processID)
    if (address.pd.first >= table->getLength()) {
        address.errorCode = 2;
        return address;
    }
    address.fd.first = table->getTable()[address.pd.first].fNumber;

    //Calc physical address
    address.fd.second = address.pd.second;
    address.logicalAndPhysicalAddress.second = address.fd.first * m_fSize + address.fd.second;
    address.errorCode = 0;

    return address;
}

//create page table for process.
PageTable *Pager::createTable(Process *process) {
    int numberOfPagse = process->getSize() / m_fSize;
    int length = numberOfPagse + 1;
    if (process->getSize() % m_fSize) {
        length++;
        numberOfPagse++;
    }

    PageTable::tableElement *table = new PageTable::tableElement[length];

    pair < bool *, int> memoryMap = m_memMap.first;

    if (memoryMap.second < 1 || memoryMap.first == nullptr) {
        return nullptr;
    }

    //search about not used frames and make the process use them.
    int index = 1;
    if (memoryMap.first) {
        for (int i = 3; i < memoryMap.second; i++) {
            if (!memoryMap.first[i]) {
                table[index].fNumber = i;
                table[index++].isValid = true;
                numberOfPagse--;
                if (!numberOfPagse) {
                    return new PageTable(process->getID(), table, length);
                }
            }
        }
    }

    //if not all pages are pointed on their own frame, start from the first allocatable frame and select them incrementally.
    //may be the same frame pointed by more than one page.
    int frameIndex = 3;
    for (int i = index; i < length; i++) {
        frameIndex = frameIndex % memoryMap.second;
        if (frameIndex == 0) {
            frameIndex = 3;
        }

        table[i].fNumber = frameIndex++;
        table[i].isValid = true;
        numberOfPagse--;
        if (!numberOfPagse) {
            goto end;
        }
    }

    end:
    return new PageTable(process->getID(), table, length);
}

//allcoate process (page table).
PageTable *Pager::talloc(PageTable *pageTable) {
    int len = pageTable->getLength();
    Process *p;
    for (int i = 0; i < len && i < m_memMap.first.second; i++) {
        if (pageTable->getTable()[i].isValid && !pageTable->getTable()[i].isInMem) {
            if (m_memMap.first.first[pageTable->getTable()[i].fNumber]) {
                 p = &m_processes[m_processMap[m_memMap.second[pageTable->getTable()[i].fNumber].first]];
                 p->getPageTable()->getTable()[m_memMap.second[pageTable->getTable()[i].fNumber].second].isInMem = false;
            }
            m_memMap.first.first[pageTable->getTable()[i].fNumber] = true;
            m_memMap.second[pageTable->getTable()[i].fNumber].first = pageTable->getProcessID();
            m_memMap.second[pageTable->getTable()[i].fNumber].second = i;
            pageTable->getTable()[i].isInMem = true;
        }
    }

    return pageTable;
}

//allocate process in memory
PageTable *Pager::palloc(Process *process) {
    //create new page table if not exist
    if (process->getPageTable() == nullptr) {
        process->setPageTable(createTable(process));
    }

    // if all pages are allocated return page table;
    if (process->isAlloc() == -1) {
        return process->getPageTable();
    }

    //try to allocate all pages with replace old pages in memory and return page table.
    return talloc(process->getPageTable());
}

//reallocate process with try to not replace any old pages in memory;
PageTable *Pager::prealloc(Process *p) {
    if (p->getPageTable() == nullptr) {
        return nullptr;
    }
    if (p->isAlloc() == -1) {
        return p->getPageTable();
    }

    // + 1 is null page which cannot be allocated.
    int allcat_count = p->isAlloc() + 1;
    vector < int > list;
    size_t index = 0;

    //search about conflict with other processes
    for (int i = 1; i < p->getPageTable()->getLength() && allcat_count < p->getPageTable()->getLength(); i++) {
        if (!p->getPageTable()->getTable()[i].isInMem &&
                m_memMap.second[p->getPageTable()->getTable()[i].fNumber].first != p->getID()) {
            list.push_back(i);
            allcat_count++;
        }
    }

    //try to change frames for conflicts.
    for (int j = 3; j < m_memMap.first.second; j++) {
        if (!m_memMap.first.first[j]) {
            p->getPageTable()->getTable()[list[index]].fNumber = j;
            p->getPageTable()->getTable()[list[index++]].isValid = true;

            if (index == list.size()) {
                break;
            }
        }
    }
    return talloc(p->getPageTable());
}

//deallcoate process from memory.
void Pager::free(Process *process) {
    if (process->isAlloc()) {
        PageTable *table = process->getPageTable();
        int len = table->getLength();
        for (int i = 0; i < len && i < m_memMap.first.second; i++) {
            if (table->getTable()[i].isInMem) {
                m_memMap.first.first[table->getTable()[i].fNumber] = false;
                m_memMap.second[table->getTable()[i].fNumber].first = -1;
                m_memMap.second[table->getTable()[i].fNumber].second = -1;
                table->getTable()[i].isInMem = false;
            }
        }
    }
}
