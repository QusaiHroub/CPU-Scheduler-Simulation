/*
 * This file is part of OS Project.
 *
 * Authors
 * Mohammad Abureesh
 * Qusai Hroub
 */


#include "sjf.hpp"

#include<map>
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
    return p1.getCpuBurst() < p2.getCpuBurst();
}

void SJF::calcCompletionTime() {
    Process *processes = getProcesses();
    int len = getProcessesSize();
    int *completionTime = new int[len];

    vector< pair <string, int> > timeLine;
    map<int, int> map;

    for (int i = 0; i < len; i++) {
        map[processes[i].getID()] = i;
    }

    m_readyQueue.push_back(processes[0]);
    completionTime[map[processes[0].getID()]] = m_readyQueue[0].getArrivalTime() + m_readyQueue[0].getCpuBurst() + getCS();
    int index = m_readyQueue.front().getID();
    int counter = 1;
    int lastTime = completionTime[map[processes[0].getID()]];

    int totalOverhead = getCS();
    int maxCompletionTime = completionTime[map[processes[0].getID()]];

    if (processes->getArrivalTime() != 0) {
        timeLine.push_back(pair<string, int>("  ", processes->getArrivalTime()));
    }
    if (getCS())
        timeLine.push_back(pair<string, int>("CS", processes->getArrivalTime() + getCS()));
    timeLine.push_back(pair<string, int>("P"  + to_string(processes->getID()), completionTime[map[processes[0].getID()]]));

    loop:
    while(!m_readyQueue.empty()) {
        m_readyQueue.erase(m_readyQueue.begin());
        for (int i = 1; i < len; i++) {
            if (!visited[i] && processes[i].getArrivalTime() <= lastTime) {
                m_readyQueue.push_back(processes[i]);
                visited[i] = true;
            }
        }

        if (counter >= len) {
            break;
        } else if (m_readyQueue.empty()) {
            for (int i = 1; i < len; i++) {
                if (!visited[i]) {
                    m_readyQueue.push_back(processes[i]);
                    index = map[m_readyQueue.front().getID()];
                    completionTime[index] = m_readyQueue[0].getArrivalTime() + m_readyQueue[0].getCpuBurst() + getCS();

                    timeLine.push_back(pair<string, int>("  ", processes[i].getArrivalTime()));
                    if (getCS())
                        timeLine.push_back(pair<string, int>("CS", processes[i].getArrivalTime() + getCS()));
                    timeLine.push_back(pair<string, int>("P" + to_string(m_readyQueue[0].getID()), completionTime[index]));

                    lastTime = completionTime[index];
                    if (maxCompletionTime < lastTime) {
                        maxCompletionTime = lastTime;
                    }
                    totalOverhead += getCS();
                    counter++;
                    goto loop;
                }
            }
        }
        sort(m_readyQueue.begin(), m_readyQueue.end(), compCPUBurst);
        index = map[m_readyQueue.front().getID()];

        completionTime[index] = lastTime + m_readyQueue[0].getCpuBurst() + getCS();

        if (getCS())
            timeLine.push_back(pair<string, int>("CS", lastTime + getCS()));
        timeLine.push_back(pair<string, int>("P" + to_string(m_readyQueue[0].getID()), completionTime[index]));

        lastTime = completionTime[index];
        counter++;
        if (maxCompletionTime < lastTime) {
            maxCompletionTime = lastTime;
        }
        totalOverhead += getCS();
    }

    setTotalOverhead(totalOverhead);
    setMaxCompletionTime(maxCompletionTime);
    setCompletionTime(completionTime);
    setTimeLine(timeLine);
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
