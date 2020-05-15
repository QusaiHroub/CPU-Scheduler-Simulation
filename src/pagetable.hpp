/*!
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

class PageTable {

public:
    struct tableElement{
        int fNumber = 0;
        bool isValid = 0;
        bool isInMem = 0;
    };

    //!constructor
    PageTable(int = -1, tableElement * = nullptr, int = 0);
    ~PageTable();


    //!functions
    int getLength();
    int getPgaeSize();
    int getProcessID();
    tableElement *getTable();
    tableElement *getDeepCopyOfTable();

private:
    
    //!Attributes
    int m_length;
    int m_processID;
    tableElement *m_table;

    //!functions
    
    //!To implements PagerTable
    void init(int, tableElement *, int = 0);
    
};

#endif //! PAGETABLE_HPP
