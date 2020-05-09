/*
 * This file is part of OS Project.
 *
 * Authors
 * Mohammad Abureesh
 *
 */

#include "process.h"
#include <iostream>


using namespace std;
class SJF
{
private:
    const int PROCESSES_SIZE;

    int m_CS;

    int* m_waitingTime = nullptr;
    int* m_turnAroundTime = nullptr;
    Process* m_processes = nullptr;

   
    void init(Process* = nullptr, int = 0);

    static bool comp(Process &, Process &);

public:
    SJF();
    SJF(Process* = nullptr,int = 0,int = 5);
    
    int* turnAroundTime();
    int* getDeepCopyOfWaitingTime();
    double avgWaitingTime();

};

