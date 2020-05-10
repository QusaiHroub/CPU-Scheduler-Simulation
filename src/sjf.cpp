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

void SJF::init() {
    Process *processes = getProcesses();
    Process *end = processes + getProcessesSize();

    sort(processes, end, comp);
    sort(processes + 1, end, compCPUBurst);

    calcCompletionTime();
    calcTurnAroundTime();
    calcWaitingTime();

    is_init = true;
}
