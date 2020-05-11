#ifndef PROCESSMANAGEMENT_HPP
#define PROCESSMANAGEMENT_HPP

#include "process.h"

class ProcessManagement {
public:
    ProcessManagement(Process * = nullptr, int = 0, int = 5);
    virtual ~ProcessManagement();

    double avgWaitingTime();
    double avgCompletionTime();
    double avgTurnAroundTime();
    double cpuUtilization();
    int *getProcessesIDs();
    int *getProcessesArrivalTime();
    int *getProcessesBurstTime();
    int *getDeepCopyOfWaitingTime();
    int *getDeepCopyOfCompletionTime();
    int *getDeepCopyOfTurnAroundTime();

private:
    const int PROCESSES_SIZE;

    Process *m_processes = nullptr;
    int m_CS;
    int m_totalOverhead;
    int m_maxCompletionTime = 0;
    bool is_init = false;

    int *m_waitingTime = nullptr;
    int *m_completionTime = nullptr;
    int *m_turnAroundTime = nullptr;

    void init(Process * = nullptr, int = 0);

protected:
    virtual void calcCompletionTime();
    virtual void calcWaitingTime();
    virtual void calcTurnAroundTime();

    int getProcessesSize();
    int getCS();
    int *getWaitingTime();
    int *getCompletionTime();
    int *getTurnAroundTime();
    Process *getProcesses();

    void setCompletionTime(int *);
    void setTotalOverhead(int);
    void setMaxCompletionTime(int);
};

#endif // PROCESSMANAGEMENT_HPP
