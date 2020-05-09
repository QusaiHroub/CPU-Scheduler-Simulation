/*
 * This file is part of OS Project.
 *
 * Authors
 * Mohammad Abureesh
 * Qusai Hroub
 */


#include "sjf.hpp"
#include <bits/stdc++.h> 
using namespace std;

SJF::SJF() : PROCESSES_SIZE(5){

}

SJF::SJF(Process* processes, int cs, int processesSize) : PROCESSES_SIZE(processesSize)
{
    if (processes == nullptr) { return; }

    init(processes, cs);
}

bool SJF::comp(Process &p1, Process &p2) {
    return p1.getArrivalTime() < p2.getArrivalTime();
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

    sort(m_processes, m_processes + PROCESSES_SIZE, comp);

    if (cs < 0) {
        cs = 0; 
    }
    m_CS = cs;


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
