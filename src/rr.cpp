#include "RR.hpp"

#include <algorithm>
#include <vector>

RR::RR(Process* processes, int cs, int processesSize, int quantum): ProcessManagement(processes, cs, processesSize) {
    if (processes == nullptr) {
        return;
    }

    init(quantum);
}

RR::~RR() {}

bool RR::comp(Process &p1, Process &p2) {
    return p1.getArrivalTime() < p2.getArrivalTime();
}

void RR::init(int quantum) {
    m_quantum = quantum;
    Process *processes = getProcesses();

    sort(processes, processes + getProcessesSize(), comp);

    calcCompletionTime();
    calcTurnAroundTime();
    calcWaitingTime();

    is_init = true;
}

void RR::calcCompletionTime() {
    int len = getProcessesSize();
    int *completionTime = new int[len];
    Process *processes = getProcesses();
    int cpuBurst[len];
    int lastTime = 0;
    int maxIndex = 0;
    vector<int> queue;
    bool isInQ[len];
    for (int i = 1; i < len; i++) {
        isInQ[i] = false;
    }
    queue.push_back(0);
    isInQ[0] = true;

    int totalOverhead = 0;
    int maxCompletionTime = lastTime;

    for (int i = 0; i < len; i++) {
        cpuBurst[i] = processes[i].getCpuBurst();
    }
    loop:
    while (!queue.empty()) {
        int index = queue.front();
        if (m_quantum < cpuBurst[index]) {
            lastTime += m_quantum + getCS();
            cpuBurst[index] -= m_quantum;
            totalOverhead += getCS();
        } else {
            lastTime += cpuBurst[index] + getCS();
            cpuBurst[index] = 0;
            completionTime[index] = lastTime;
            if (lastTime > maxCompletionTime) {
                maxCompletionTime = lastTime;
            }
            totalOverhead += getCS();
        }

        if (maxIndex < index) {
            maxIndex = index;
        }

        for (int i = index + 1; i < len; i++) {
            if (!isInQ[i] && processes[i].getArrivalTime() <= lastTime) {
                queue.push_back(i);
                isInQ[i] = true;
            }
        }

        if (cpuBurst[index]) {
            queue.push_back(index);
        }
        queue.erase(queue.begin());

        if (maxIndex + 1 < len && queue.empty()) {
            queue.push_back(maxIndex + 1);
            lastTime = processes[queue.front()].getArrivalTime();
            goto loop;
        }

    }

    setTotalOverhead(totalOverhead);
    setMaxCompletionTime(maxCompletionTime);
    setCompletionTime(completionTime);
}
