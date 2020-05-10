/*
 * This file is part of OS Project.
 *
 * Authors
 * Mohammad Abureesh
 * Qusai Hroub
 */


#include "sjf.hpp"
#include<algorithm>
using namespace std;

SJF::SJF(Process* processes, int cs, int processesSize) : ProcessManagement(processes, cs, processesSize)
{
    if (processes == nullptr) {
        return;
    }

    init();
}

SJF::~SJF() {

}

bool SJF::comp(Process &p1, Process &p2) {
    return p1.getArrivalTime() < p2.getArrivalTime();
}

bool SJF::compCPUBurst(Process &p1, Process &p2) {
    return p1.getCpuBurs() < p2.getCpuBurs();
}

void SJF::calcCompletionTime() {
    Process *processes = getProcesses();
    int len = getProcessesSize();
    int *completionTime = new int[len];
    m_readyQueue.push_back(processes[0]);
    completionTime[0] = m_readyQueue[0].getArrivalTime() + m_readyQueue[0].getCpuBurs() + getCS();
    int index = 1;
    int lastTime = completionTime[0];
    while(!m_readyQueue.empty()) {
        m_readyQueue.erase(m_readyQueue.begin());
        for (int i = 1; i < len; i++) {
            if (!visited[i] && processes[i].getArrivalTime() <= lastTime) {
                m_readyQueue.push_back(processes[i]);
                visited[i] = true;
            }
        }
        if (m_readyQueue.empty()) {
            break;
        }
        sort(m_readyQueue.begin(), m_readyQueue.end(), compCPUBurst);
        completionTime[index] = completionTime[index - 1] + m_readyQueue[0].getCpuBurs() + getCS();
        lastTime = completionTime[index++];
    }
    setCompletionTime(completionTime);
}

void SJF::init() {
    Process *processes = getProcesses();
    Process *end = processes + getProcessesSize();

    sort(processes, end, comp);

    if (visited != nullptr) {
        delete visited;
        visited = nullptr;
    }
    visited = new bool[getProcessesSize()];
    for (int i = 0; i < getProcessesSize(); i++) {
        visited[i] = false;
    }

    calcCompletionTime();
    calcTurnAroundTime();
    calcWaitingTime();

    is_init = true;
    delete visited;
    visited = nullptr;
}
