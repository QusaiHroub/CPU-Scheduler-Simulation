#include "operations.h"

Operations::Operations() {}


//FCFS algorithm
int * Operations::WaitingTime_FCFS(Process *processes) {
    if (processes == nullptr) {
        return nullptr;
    }

    //waiting time for p1
    m_waitingTime[0] = 0;

    for (int i = 1; i < 5; i++) {
        m_waitingTime[i] = processes[i - 1].getCpuBurs() + m_waitingTime[i - 1];
    }

    //for (int i = 0; i < 5; i++) { cout << "\nwaiting Time for process" << i + 1 << " : " << waitingTime[i] << endl; }
    return m_waitingTime;
}

int * Operations::TurnAroundTime_FCFS(Process *processes) {
    if (processes == nullptr) {
        return nullptr;
    }

    for (int i = 0; i < 5; i++) {
        m_turnAroundTime[i] = processes[i].getCpuBurs() + m_waitingTime[i];
    }

    //for (int i = 0; i < 5; i++) { cout << "\nTurn around Time for process" << i + 1 << " : " << TurnAroundTime[i] << endl; }
    return m_turnAroundTime;
}

double Operations::AvgWaitingTime_FCFS() {
    double total_Wt = 0;
    for (int i = 0; i < 5; i++) {
        total_Wt += m_waitingTime[i];
    }

    //cout << "Average waiting Time = " << total_Wt / 5 << endl;
    return  total_Wt / 5;
}
// end FCFS algorithm
