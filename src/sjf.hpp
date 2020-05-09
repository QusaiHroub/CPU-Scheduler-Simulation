/*
 * This file is part of OS Project.
 *
 * Authors
 * Mohammad Abureesh
 * Qusai Hroub
 */

#include "process.h"

class SJF
{
private:
    const int PROCESSES_SIZE;

    int m_CS;

    int* m_waitingTime = nullptr;
    int* m_turnAroundTime = nullptr;
    Process* m_processes = nullptr;

   
    void arrangerArrival(Process * = nullptr);
    void init(Process* = nullptr, int = 0);

public:
    SJF();
    SJF(Process* = nullptr,int = 0,int = 5);
    
    int* turnAroundTime();
    int* getDeepCopyOfWaitingTime();
    double avgWaitingTime();

};

