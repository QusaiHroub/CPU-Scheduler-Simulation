/*
 * This file is part of OS Project.
 *
 * Authors
 * Qusai Hroub
 * Mohammad Abureesh
 *
 */

#include <algorithm>

#include "processmanagement.hpp"
#include "process.h"

ProcessManagement::ProcessManagement(Process *processes, int cs, int processesSize) : PROCESSES_SIZE(processesSize) {
    if (processes == nullptr) {
        return;
    }

    init(processes, cs);
}

ProcessManagement::~ProcessManagement() {
    if (m_processes != nullptr) {
        delete m_processes;
    }

    if (m_waitingTime != nullptr) {
        delete m_waitingTime;
    }

    if (m_completionTime != nullptr) {
        delete m_completionTime;
    }

    if (m_turnAroundTime != nullptr) {
        delete m_turnAroundTime;
    }
}

void ProcessManagement::calcCompletionTime() {
    if (m_completionTime != nullptr) {
        delete m_completionTime;
    }
    m_completionTime = new int[PROCESSES_SIZE];
    m_completionTime[0] = m_processes->getArrivalTime() + m_processes->getCpuBurst() + m_CS;
    m_totalOverhead = m_CS;
    for (int i = 1; i < PROCESSES_SIZE; i++) {
        if (m_completionTime[i - 1] > m_processes[i].getArrivalTime()) {
            m_completionTime[i] = m_completionTime[i - 1] + m_processes[i].getCpuBurst() + m_CS;
        } else {
            m_completionTime[i] = m_processes[i].getArrivalTime() + m_processes[i].getCpuBurst() + m_CS;
        }
        if (m_completionTime[i] > m_maxCompletionTime) {
            m_maxCompletionTime = m_completionTime[i];
        }
        m_totalOverhead += m_CS;
    }
}

void ProcessManagement::calcWaitingTime() {
    if (m_waitingTime != nullptr) {
        delete m_waitingTime;
        m_waitingTime = nullptr;
    }
    m_waitingTime = new int[PROCESSES_SIZE];

    for (int i = 0; i < PROCESSES_SIZE; i++) {
        m_waitingTime[i] = m_turnAroundTime[i] - m_processes[i].getCpuBurst();
    }
}

void ProcessManagement::calcTurnAroundTime() {
    if (m_turnAroundTime != nullptr) {
        delete m_turnAroundTime;
        m_turnAroundTime = nullptr;
    }
    m_turnAroundTime = new int[PROCESSES_SIZE];

    for (int i = 0; i < PROCESSES_SIZE; i++) {
        m_turnAroundTime[i] = m_completionTime[i] - m_processes[i].getArrivalTime();
    }
}

void ProcessManagement::init(Process *processes, int cs) {
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
    is_init = true;
}

double ProcessManagement::avgWaitingTime() {
    if (m_waitingTime == nullptr) {
        return -1;
    }

    double total_Wt = 0;
    for (int i = 0; i < PROCESSES_SIZE; i++) {
        total_Wt += m_waitingTime[i];
    }

    return  total_Wt / PROCESSES_SIZE;
}

double ProcessManagement::avgCompletionTime() {
    if (m_completionTime == nullptr) {
        return -1;
    }

    double total_Ct = 0;
    for (int i = 0; i < PROCESSES_SIZE; i++) {
        total_Ct += m_completionTime[i];
    }

    return  total_Ct / PROCESSES_SIZE;
}

double ProcessManagement::avgTurnAroundTime() {
    if (m_turnAroundTime == nullptr) {
        return -1;
    }

    double total_Tt = 0;
    for (int i = 0; i < PROCESSES_SIZE; i++) {
        total_Tt += m_turnAroundTime[i];
    }

    return  total_Tt / PROCESSES_SIZE;
}

int *ProcessManagement::getDeepCopyOfWaitingTime() {
    int *waitingTime = new int[PROCESSES_SIZE];
    for (int i = 0; i < PROCESSES_SIZE; i++) {
        waitingTime[i] = m_waitingTime[i];
    }
    return waitingTime;
}

int *ProcessManagement::getDeepCopyOfCompletionTime() {
    int *competionTime = new int[PROCESSES_SIZE];
    for (int i = 0; i < PROCESSES_SIZE; i++) {
        competionTime[i] = m_completionTime[i];
    }
    return competionTime;
}

int *ProcessManagement::getDeepCopyOfTurnAroundTime() {
    int *turnAroundTime = new int[PROCESSES_SIZE];
    for (int i = 0; i < PROCESSES_SIZE; i++) {
        turnAroundTime[i] = m_turnAroundTime[i];
    }
    return turnAroundTime;
}

Process *ProcessManagement::getProcesses() {
    return m_processes;
}

int ProcessManagement::getProcessesSize() {
    return PROCESSES_SIZE;
}

int *ProcessManagement::getWaitingTime() {
    return m_waitingTime;
}

int ProcessManagement::getCS() {
    return m_CS;
}

void ProcessManagement::setCompletionTime(int *completionTime) {
    if (m_completionTime != nullptr) {
        delete m_completionTime;
    }

    m_completionTime = completionTime;
}

void ProcessManagement::setTotalOverhead(int totalOverhead) {
    m_totalOverhead = totalOverhead;
}

void ProcessManagement::setMaxCompletionTime(int maxCompletionTime) {
    m_maxCompletionTime = maxCompletionTime;
}

double ProcessManagement::cpuUtilization() {
    return double(m_maxCompletionTime - m_totalOverhead) / m_maxCompletionTime;
}
