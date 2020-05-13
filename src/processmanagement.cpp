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

/*
This constructor receives an array of Processes, context Switch (CS), 
and the size of the Processes, and if the array equals nullptr, 
it returns and does not implement the algorithm. Otherwise, it calls the function that implements the algorithm init().
*/
ProcessManagement::ProcessManagement(Process *processes, int cs, int processesSize) : PROCESSES_SIZE(processesSize) {
    if (processes == nullptr) {
        return;
    }

    
   /*
     call this function for initialization processes Management
     this function receives two parameters array of processes and context switch.
   */
    init(processes, cs);
}


/*
deconstructor.
If any pointer in this class is not free, this pointer will be deleted.
*/
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

//To calculation Completion time.
void ProcessManagement::calcCompletionTime() {
    if (m_completionTime != nullptr) {
        delete m_completionTime;
    }
    m_completionTime = new int[PROCESSES_SIZE];
    m_completionTime[0] = m_processes->getArrivalTime() + m_processes->getCpuBurst() + m_CS;
    m_totalOverhead = m_CS;

    if (m_processes->getArrivalTime() != 0) {
        m_timeLine.push_back(pair<string, int>("  ", m_processes->getArrivalTime()));
    }
    if (m_CS)
        m_timeLine.push_back(pair<string, int>("CS", m_processes->getArrivalTime() + m_CS));
    m_timeLine.push_back(pair<string, int>("P"  + to_string(m_processes->getID()), m_completionTime[0]));

    
    /*
     calculate the completion time for each process.
     completion time equal completion time plus CPU Burst plus Context Switch. 
    */
    for (int i = 1; i < PROCESSES_SIZE; i++) {

        if (m_completionTime[i - 1] >= m_processes[i].getArrivalTime()) {
            m_completionTime[i] = m_completionTime[i - 1] + m_processes[i].getCpuBurst() + m_CS;

            if (m_CS)
                m_timeLine.push_back(pair<string, int>("CS", m_completionTime[i - 1] + m_CS));
            m_timeLine.push_back(pair<string, int>("P" + to_string(m_processes[i].getID()), m_completionTime[i]));
        } else {
            m_completionTime[i] = m_processes[i].getArrivalTime() + m_processes[i].getCpuBurst() + m_CS;

            m_timeLine.push_back(pair<string, int>("  ", m_processes[i].getArrivalTime()));
            if (m_CS)
                m_timeLine.push_back(pair<string, int>("CS", m_processes[i].getArrivalTime() + m_CS));
            m_timeLine.push_back(pair<string, int>("P" + to_string(m_processes[i].getID()), m_completionTime[i]));
        }
        
        //change max completion time
        if (m_completionTime[i] > m_maxCompletionTime) {
            m_maxCompletionTime = m_completionTime[i];
        }
        
        //add context switch to m_totaloverhead 
        m_totalOverhead += m_CS;
    }
}


/*
To find Waiting time.
waiting time equal turn around time minus CPU Burst.
*/
void ProcessManagement::calcWaitingTime() {
    if (m_waitingTime != nullptr) {
        delete m_waitingTime;
        m_waitingTime = nullptr;
    }
    
    //declaration <m_waitingTime> to store waiting time for each process
    m_waitingTime = new int[PROCESSES_SIZE];
    
    //To add waiting time for each process to array <m_waitingTime>
    for (int i = 0; i < PROCESSES_SIZE; i++) {
        m_waitingTime[i] = m_turnAroundTime[i] - m_processes[i].getCpuBurst();
    }
}

/*
To find turn around time.
turn around time equal completion time minus arrival time.
*/
void ProcessManagement::calcTurnAroundTime() {
    if (m_turnAroundTime != nullptr) {
        delete m_turnAroundTime;
        m_turnAroundTime = nullptr;
    }
    
   //declaration<m_turnAroundTime> to store turn around time for each process
    m_turnAroundTime = new int[PROCESSES_SIZE];

    //To add turn around time for each process to array <m_turnAroundTime>
    for (int i = 0; i < PROCESSES_SIZE; i++) {
        m_turnAroundTime[i] = m_completionTime[i] - m_processes[i].getArrivalTime();
    }
}


//this function work on implementation Process Management for any algorithm  in this program
void ProcessManagement::init(Process *processes, int cs) {
    if (processes == nullptr) {
        return;
    }

    if (m_processes != nullptr) {
        delete m_processes;
    }
    
     //declaration<m_processes> to store all Processes
    m_processes = new Process[PROCESSES_SIZE];
    
    /*
    to add operations to the <m_processes> array from array <processes>
    <processes>This array is passed to the function init().
    */
    for (int i = 0; i < PROCESSES_SIZE; i++) {
        m_processes[i] = processes[i];
    }

    //check if context Switch less than zero.
    if (cs < 0) {
        cs = 0;
    }
    m_CS = cs;
    is_init = true;
}


/*
To computes the average wait time
this function return Average .
Average wait time is the sum of equal waiting time for each process
Divide the Processes size
*/
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


/*
To computes the average completion time
this function return Average.
Average completion time is the sum of equal completion time for each process Divide the Processes size
*/
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


/*
To computes the average turn around time
this function return Average.
Average turn around time is the sum of equal completion time for each process Divide the Processes size
*/
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


/*
To return Copy of an array <m_waitingTime>
Declared new array of type integer <waitingTime>.
Store all items array<m_waitingTime> in array  <waitingTime>.
*/
int *ProcessManagement::getDeepCopyOfWaitingTime() {
    int *waitingTime = new int[PROCESSES_SIZE];
    for (int i = 0; i < PROCESSES_SIZE; i++) {
        waitingTime[i] = m_waitingTime[i];
    }
    return waitingTime;
}


/*
To return Copy of an array <m_completionTime>
Declared new array of type integer <competionTime>.
Store all items array<m_completionTime> in array  <competionTime>.
*/
int *ProcessManagement::getDeepCopyOfCompletionTime() {
    int *competionTime = new int[PROCESSES_SIZE];
    for (int i = 0; i < PROCESSES_SIZE; i++) {
        competionTime[i] = m_completionTime[i];
    }
    return competionTime;
}


/*
To return Copy of an array <m_turnAroundTime>
Declared new array of type integer <turnAroundTime>.
Store all items array <m_turnAroundTime> in array  <turnAroundTime>.
*/
int *ProcessManagement::getDeepCopyOfTurnAroundTime() {
    int *turnAroundTime = new int[PROCESSES_SIZE];
    for (int i = 0; i < PROCESSES_SIZE; i++) {
        turnAroundTime[i] = m_turnAroundTime[i];
    }
    return turnAroundTime;
}


//To return an array of processes
Process *ProcessManagement::getProcesses() {
    return m_processes;
}

//To return Processes size
int ProcessManagement::getProcessesSize() {
    return PROCESSES_SIZE;
}

//To return this array m_waitingTime
int *ProcessManagement::getWaitingTime() {
    return m_waitingTime;
}

//To return Context switch
int ProcessManagement::getCS() {
    return m_CS;
}

/*
It receives one integer type array and assigns it
to the<m_completionTime> array in this class.
*/
void ProcessManagement::setCompletionTime(int *completionTime) {
    if (m_completionTime != nullptr) {
        delete m_completionTime;
    }

    m_completionTime = completionTime;
}

//To change total overhead
void ProcessManagement::setTotalOverhead(int totalOverhead) {
    m_totalOverhead = totalOverhead;
}

//To change max Completion Time
void ProcessManagement::setMaxCompletionTime(int maxCompletionTime) {
    m_maxCompletionTime = maxCompletionTime;
}


/*
To return CPU utilization.
CPU utilization is equal to maximum completion time minus total overhead Divided on maximum completion time.
*/
double ProcessManagement::cpuUtilization() {
    return double(m_maxCompletionTime - m_totalOverhead) / m_maxCompletionTime;
}

//To return a list of Processes Ids.
int *ProcessManagement::getProcessesIDs() {
    int * list = new int[PROCESSES_SIZE];
    for (int i = 0; i < PROCESSES_SIZE; i++) {
        list[i] = m_processes[i].getID();
    }

    return list;
}

//To return a list of Processes Arrival Time.
int *ProcessManagement::getProcessesArrivalTime() {
    int * list = new int[PROCESSES_SIZE];
    for (int i = 0; i < PROCESSES_SIZE; i++) {
        list[i] = m_processes[i].getArrivalTime();
    }

    return list;
}

//To return a list of Processes Burst time.
int *ProcessManagement::getProcessesBurstTime() {
    int * list = new int[PROCESSES_SIZE];
    for (int i = 0; i < PROCESSES_SIZE; i++) {
        list[i] = m_processes[i].getCpuBurst();
    }

    return list;
}

//To return Time line
vector<pair<string, int>> &ProcessManagement::getTimeLine() {
    return m_timeLine;
}

//To change Time line
void ProcessManagement::setTimeLine(vector<pair<string, int> > &timeLine) {
    for (size_t i = 0; i < timeLine.size(); i++) {
        m_timeLine.push_back(timeLine[i]);
    }
}
