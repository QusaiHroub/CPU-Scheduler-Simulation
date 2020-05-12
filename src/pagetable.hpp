#ifndef PAGETABLE_HPP
#define PAGETABLE_HPP

#include "process.h"

class PageTable {

public:
    PageTable(Process * = nullptr, int = 128, pair<bool *, int> = pair<bool *, int> (nullptr, 0));
    ~PageTable();

    struct tableElement{
        int fNumber = 0;
        bool isValid = 0;
        bool isInMem = 0;
    };

    int getLength();
    int getPgaeSize();
    int getProcessID();
    tableElement *getTable();
    tableElement *getDeepCopyOfTable();

private:
    int m_length;
    int m_pageSize;
    tableElement *m_table;
    Process *m_process;
    pair<bool *, int> m_memoryMap;

    void init();
    void setPageSize(int);
};

#endif // PAGETABLE_HPP
