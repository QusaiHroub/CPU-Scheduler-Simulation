/*
 * This file is part of OS Project.
 *
 * Authors
 * Mohammad Abureesh
 *
 */

#include "process.h"

class SJF
{
private:
    const int PROCESSES_SIZE;
    bool check = false;

    int m_CS;

    int* m_waitingTime = nullptr;
    int* m_turnAroundTime = nullptr;
    Process* m_processes = nullptr;

    void swap(Process, Process);
    void arrangerArrival();
    void init(Process* = nullptr, int = 0);

public:
    SJF();
    SJF(Process* = nullptr,int = 0,int = 5);
    
    int* turnAroundTime();
    int* getDeepCopyOfWaitingTime();
    double avgWaitingTime();

};

