/*
 * This file is part of OS Project.
 *
 * Authors
 * Qusai Hroub
 * Mohammad Abureesh
 *
 * Page Table
 */

#ifndef PAGETABLE_HPP
#define PAGETABLE_HPP

#include "process.h"

class PageTable {

public:
    
    //constructor
    PageTable(Process * = nullptr, int = 128, pair<bool *, int> = pair<bool *, int> (nullptr, 0));
    ~PageTable();

    struct tableElement{
        int fNumber = 0;
        bool isValid = 0;
        bool isInMem = 0;
    };

    //functions
    int getLength();
    int getPgaeSize();
    int getProcessID();
    tableElement *getTable();
    tableElement *getDeepCopyOfTable();

private:
    
    //Attributes
    int m_length;
    int m_pageSize;
    tableElement *m_table;
    Process *m_process;
    pair<bool *, int> m_memoryMap;

    //functions
    
    //To implements PagerTable
    void init();
    
    //To change Frame size (page size)
    void setPageSize(int);
};

#endif // PAGETABLE_HPP
