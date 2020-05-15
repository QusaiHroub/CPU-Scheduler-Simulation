/*!
 * This file is part of OS Project.
 *
 * Authors
 * Qusai Hroub
 * Mohammad Abureesh
 *
 * Process structure
 * 
 */

#pragma once
#include<iostream>

#include "pagetable.hpp"

using namespace std;

class Process
{
private:

    //!Attributes for each process
    int m_arrivalTime;
    int m_cpuBurst;
	
    //! size in Bytes
    int m_size;   
    int m_id;

    PageTable *m_pageTable = nullptr;

public:
    
    //!Constructor
    Process();
    Process(int, int, int, int);
    ~Process();

    //!getters and setters
	
    int getArrivalTime();
    int getCpuBurst();
    int getSize();
    int getID();
    int isAlloc();

    void setArrivalTime(int);
    void setCPUBurst(int);
    void setSize(int);
    void setID(int);
    void setPageTable(PageTable *);

    PageTable *getPageTable();

};


