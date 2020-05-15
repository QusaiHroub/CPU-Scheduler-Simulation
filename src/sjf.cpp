/*!
 * This file is part of OS Project.
 *
 * Authors
 * Mohammad Abureesh
 * Qusai Hroub
 *
 * C++ program for implementation of FCFS algorithm
 * this file, declaration for "SJF.hpp"
 */


#include "sjf.hpp"

#include<map>
#include<algorithm>

using namespace std;

/*!
This constructor receives an array of Processes, context Switch (CS), 
and the size of the operations, and if the array equals nullptr, 
it returns and does not implement the algorithm. Otherwise, it calls the function that implements the algorithm init().
*/
SJF::SJF(Process* processes, int cs, int processesSize) : ProcessManagement(processes, cs, processesSize)
{
    if (processes == nullptr) {
        return;
    }

    //!call this function for implements SJF algorithm
    init();
}

//!deconstructor
SJF::~SJF() {

}

//!this function return true, when the arrival time of the first process is less than the arrival time of the second process.
bool SJF::comp(Process &p1, Process &p2) {
    return p1.getArrivalTime() < p2.getArrivalTime();
}

//!this function return true, when the CPU Bursy of the first process is less than the CPU Burst of the second process.
bool SJF::compCPUBurst(Process &p1, Process &p2) {
    return p1.getCpuBurst() < p2.getCpuBurst();
}

//! Function to calculate Completion Time for SJF algorithm
void SJF::calcCompletionTime() {
    
    //!Declare an array of Processes
    Process *processes = getProcesses();
    int len = getProcessesSize();
    
    //!Declare an array integer to store the end time for each process
    int *completionTime = new int[len];

    vector< pair <string, int> > timeLine;
    
    //!To create a map with a key of the type integer,and value of type integer
    map<int, int> map;

    //!To add into the <map>
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

    //!Start loop
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
        } else if (m_readyQueue.empty()) { //!check if the ready queue is empty and all processes are not processed then start from the remaining process that has the shortest arrival time.
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
                    
                    //! Increment counter
                    counter++;
                    
                    //!Jumped to label <loop>
                    goto loop;
                }
            }
        }

        //!Arrange the Processes in ready queue based on its cpu burst before continuing the calculations
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

//!this function work on implementation <SJF> algorithm
void SJF::init() {
    Process *processes = getProcesses();
    Process *end = processes + getProcessesSize();

    //!Arrange the Processes based on the arrival time before starting the calculations
    sort(processes, end, comp);

    if (visited != nullptr) {
        delete visited;
        visited = nullptr;
    }

    //!init the list of visited processes, that we use to determine if the process entered the queue or not.
    visited = new bool[getProcessesSize()];
    for (int i = 0; i < getProcessesSize(); i++) {
        visited[i] = false;
    }

    calcCompletionTime();
    calcTurnAroundTime();
    calcWaitingTime();

    //!As long as this variable equals true means that the algorithm has been implemented
    is_init = true;
    
    delete visited;
    visited = nullptr;
}
