/*
 * This file is part of OS Project.
 *
 * Authors
 * Mohammad Abureesh
 * Qusai Hroub
 */


#include "sjf.hpp"

SJF::SJF() : PROCESSES_SIZE(5){

}

SJF::SJF(Process* processes, int cs, int processesSize) : PROCESSES_SIZE(processesSize)
{
    if (processes == nullptr) { return; }

    init(processes, cs);
}


//sort the processes according to their arrival time
void SJF::arrangerArrival(Process *processes)
{
    if (processes == nullptr|| m_processes == nullptr) {
        return;
    }
   

    int min = processes[0].getArrivalTime();
    
    for (int i = 0; i < PROCESSES_SIZE; i++) 
    {
        for (int j = 0; j < PROCESSES_SIZE; j++) 
        {
            if (processes[j].getArrivalTime() < min) 
            {
                min = processes[j].getArrivalTime();
                m_processes[i] = processes[j];
            }
        }
    }
}

void SJF::init(Process* processes, int cs)
{
    if (processes == nullptr) {
        return;
    }

    m_processes = new Process[PROCESSES_SIZE];
    for (int i = 0; i < PROCESSES_SIZE; i++) 
    {
        m_processes[i] = processes[i];
    }

    if (cs < 0) {
        cs = 0; 
    }
    m_CS = cs;

    arrangerArrival(m_processes);

    m_waitingTime = new int[PROCESSES_SIZE];
    //waiting Time for p1
    m_waitingTime[0] = 0;

    for (int i = 1; i < PROCESSES_SIZE; i++) {
        m_waitingTime[i] = processes[i - 1].getCpuBurs() + m_waitingTime[i - 1] + m_CS;
    }

}

int* SJF::turnAroundTime() 
{
    if (m_processes == nullptr) {
        return nullptr;
    }

    arrangerArrival(m_processes);

    for (int i = 0; i < PROCESSES_SIZE; i++)
    {
        m_turnAroundTime[i] = m_processes[i].getCpuBurs() + m_waitingTime[i];
    }

    return m_turnAroundTime;
}

double SJF::avgWaitingTime() 
{
    if (m_waitingTime == nullptr) {
        return -1;
    }

    double total_wt = 0;
    for (int i = 0; i < PROCESSES_SIZE; i++)
    {
        total_wt += m_waitingTime[i];
    }

    return total_wt / PROCESSES_SIZE;
}

int* SJF::getDeepCopyOfWaitingTime() 
{
    int* waitingTime = new int[PROCESSES_SIZE];
    for (int i = 0; i < PROCESSES_SIZE; i++) {
        waitingTime[i] = m_waitingTime[i];
    }

    return waitingTime;
}
