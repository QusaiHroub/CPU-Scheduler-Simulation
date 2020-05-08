#include <iostream>
#include <cmath>
#include "process.h"

using namespace std;

class Operations {
private:
    int m_waitingTime[5];
    int m_turnAroundTime[5];

public:
    Operations();

    //FCFS algorithm
    int * WaitingTime_FCFS(Process * = nullptr);
    int * TurnAroundTime_FCFS(Process * = nullptr);
    double AvgWaitingTime_FCFS();
    // end FCFS algorithm
};
