/*
 * This file is part of OS Project.
 *
 * Authors
 * Mohammad Abureesh
 * Qusai Hroub
 *
 * Process Management
 * Use this class for all scheduling algorithms in this program
 * 
 */

#ifndef PROCESSMANAGEMENT_HPP
#define PROCESSMANAGEMENT_HPP

#include "process.h"

#include <vector>
#include <string>

class ProcessManagement {
public:
    
     //constructors
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
    vector< pair <string, int> > &getTimeLine();

private:
    
    //Numbers of Processes in File
    const int PROCESSES_SIZE;
    
    //Attributes
    Process *m_processes = nullptr;
    int m_CS;
    int m_totalOverhead;
    int m_maxCompletionTime = 0;
    bool is_init = false;

    int *m_waitingTime = nullptr;
    int *m_completionTime = nullptr;
    int *m_turnAroundTime = nullptr;    
    //end attributes
    
    vector< pair <string, int> > m_timeLine;
    
     //this Function initializes for Processes Management 
    void init(Process * = nullptr, int = 0);

protected:
    // virtual functions
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
    void setTimeLine(vector< pair <string, int> > &);
};

#endif // PROCESSMANAGEMENT_HPP
