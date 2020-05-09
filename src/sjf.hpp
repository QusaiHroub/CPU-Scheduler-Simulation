/*
 * This file is part of OS Project.
 *
 * Authors
 * Mohammad Abureesh
 *
 */


#include "sjf.hpp"

SJF::SJF() : PROCESSES_SIZE(5) {}

SJF::SJF(Process* processes, int cs, int processesSize) : PROCESSES_SIZE(processesSize)
{
    if (processes == nullptr) { return; }

    init(processes, cs);
}


//sort the processes according to their arrival time
void SJF::arrangerArrival(Process *processes)
{
    if (processes == nullptr) {
        return;
    }

    int min = processes[0].getArrivalTime();
    for (int i = 0; i < PROCESSES_SIZE; i++) 
    {
        if (m_processes[i].getArrivalTime()<min) 
        {
            m_processes[i] = processes[i];
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
}

