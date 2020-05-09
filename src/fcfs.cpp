/*
 * This file is part of OS Project.
 *
 * Authors
 * Qusai Hroub
 * Mohammad Abureesh
 *
 */

#include "fcfs.hpp"

FCFS::FCFS() : PROCESSES_SIZE(5){

}

FCFS::FCFS(Process *processes, int cs, int processesSize) : PROCESSES_SIZE(processesSize) {
    if (processes == nullptr) {
        return;
    }

    init(processes, cs);
}

FCFS::~FCFS() {
    if (m_processes != nullptr) {
        delete m_processes;
    }

    if (m_waitingTime != nullptr) {
        delete m_waitingTime;
    }
}

void FCFS::init(Process *processes, int cs) {
    if (processes == nullptr) {
        return;
    }

    if (m_processes != nullptr) {
        delete m_processes;
    }
    m_processes = new Process[PROCESSES_SIZE];
    for (int i = 0; i < PROCESSES_SIZE; i++) {
        m_processes[i] = processes[i];
    }
    if (cs < 0) {
        cs = 0;
    }
    m_CS = cs;

    if (m_waitingTime != nullptr) {
        delete m_waitingTime;
        m_waitingTime = nullptr;
    }
    m_waitingTime = new int[PROCESSES_SIZE];

    //waiting time for p1
    m_waitingTime[0] = 0;

    for (int i = 1; i < PROCESSES_SIZE; i++) {
        m_waitingTime[i] = processes[i - 1].getCpuBurs() + m_waitingTime[i - 1] + m_CS;
    }

    is_init = true;
}

int *FCFS::turnAroundTime() {
    if (m_processes == nullptr) {
        return nullptr;
    }

    int *turnAroundTime = new int[PROCESSES_SIZE];

    for (int i = 0; i < 5; i++) {
        turnAroundTime[i] = m_processes[i].getCpuBurs() + m_waitingTime[i];
    }

    return turnAroundTime;
}

double FCFS::avgWaitingTime() {
    if (m_waitingTime == nullptr) {
        return -1;
    }

    double total_Wt = 0;
    for (int i = 0; i < PROCESSES_SIZE; i++) {
        total_Wt += m_waitingTime[i];
    }

    //cout << "Average waiting Time = " << total_Wt / 5 << endl;
    return  total_Wt / PROCESSES_SIZE;
}

int *FCFS::getDeepCopyOfWaitingTime() {
    int *waitingTime = new int[PROCESSES_SIZE];
    for (int i = 0; i < PROCESSES_SIZE; i++) {
        waitingTime[i] = m_waitingTime[i];
    }
    return waitingTime;
}
