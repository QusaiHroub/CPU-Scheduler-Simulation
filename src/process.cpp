/*
 * This file is part of OS Project.
 *
 * Authors
 * Qusai Hroub
 * Mohammad Abureesh
 *
 */

#include "process.h"

/*
This constructor receives process ID, arrival time, CPU burst, and size for each process.
size in bytes for each process, and Passing these values via <setters> 
*/
Process::Process(int id, int arrivalTime, int cpuBurst, int size) {
    setID(id);
    setArrivalTime(arrivalTime);
    setCPUBurst(cpuBurst);
    setSize(size);
}

//Default constructor
Process::Process() {}

Process::~Process() {
    if (!m_pageTable) {
        delete m_pageTable;
    }
}

//this function return id for process 
int Process::getID() {
    return m_id;
}

//this function return Arrival time for process 
int Process::getArrivalTime() {
    return m_arrivalTime;
}

//this function return CPU Burst for process 
int Process::getCpuBurst() {
    return m_cpuBurst;
}

//this function return size for process 
int Process::getSize() {
    return m_size;
}

//To change Process id
void Process::setID(int id) {
    m_id = id;
}

//To change Process arrival time
void Process::setArrivalTime(int arrivalTime) {
    m_arrivalTime = arrivalTime;
}

//To change Process CPU Burst
void Process::setCPUBurst(int cpuBurst) {
    m_cpuBurst = cpuBurst;
}

//To change Process Size
void Process::setSize(int size) {
    m_size = size;
}

PageTable *Process::getPageTable() {
    return m_pageTable;
}

//return -1 if all pages are allocated, 0 if all pages not allocated, positive number if some pages are allocated and the number ecqual to number of allocated pages.
int Process::isAlloc() {
    if (m_pageTable == nullptr) {
        return false;
    }
    int sum = 0;
    for (int i = 0; i < m_pageTable->getLength(); i++) {
        sum += m_pageTable->getTable()[i].isInMem;
    }
    if (sum + 1 == m_pageTable->getLength()) {
        return -1;
    }
    return sum;
}

void Process::setPageTable(PageTable *pageTable) {
    if (m_pageTable != nullptr) {
        delete m_pageTable;
    }
    m_pageTable = pageTable;
}
