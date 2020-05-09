/*
 * This file is part of OS Project.
 *
 * Authors
 * Qusai Hroub
 * Mohammad Abureesh
 *
 */

#include <algorithm>

#include "fcfs.hpp"

FCFS::FCFS(Process *processes, int cs, int processesSize): ProcessManagement(processes, cs, processesSize) {
    if (processes == nullptr) {
        return;
    }

    init();
}

FCFS::~FCFS() {

}

bool FCFS::comp(Process &p1, Process &p2) {
    return p1.getArrivalTime() < p2.getArrivalTime();
}

void FCFS::init() {
    Process *processes = getProcesses();

    sort(processes, processes + getProcessesSize(), comp);

    calcCompletionTime();
    calcTurnAroundTime();
    calcWaitingTime();

    is_init = true;
}
