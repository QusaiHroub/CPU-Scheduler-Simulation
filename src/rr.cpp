/*!
 * This file is part of OS Project.
 *
 * Authors
 * Qusai Hroub
 * Mohammad Abureesh
 *
 * RR algorithm
 *
 */

#include "RR.hpp"

#include <algorithm>
#include <vector>

/*!
This constructor receives an array of Processes, context Switch (CS), 
the size of the operations and Quantum, and if the array equals nullptr, 
it returns and does not implement the algorithm. Otherwise, it calls the function that implements the algorithm init().
*/
RR::RR(Process* processes, int cs, int processesSize, int quantum): ProcessManagement(processes, cs, processesSize) {
    if (processes == nullptr) {
        return;
    }

    //!call this function for implements RR algorithm
    init(quantum);
}

//!deconstructor
RR::~RR() {}

 /*!
the comparison function.
this function receives two processes.
return true if arrival time for the first process less than arrival time for the second process.
*/
bool RR::comp(Process &p1, Process &p2) {
    return p1.getArrivalTime() < p2.getArrivalTime();
}

/*!
this function work on implementation <RR> algorithm
receive one integer Parameter (quantum) for use in this algorithm.
*/
void RR::init(int quantum) {
    m_quantum = quantum;
    
    
    Process *processes = getProcesses();

    //!Arrange the Processes based on the arrival time before starting the calculations
    sort(processes, processes + getProcessesSize(), comp);

    calcCompletionTime();
    calcTurnAroundTime();
    calcWaitingTime();

   //!As long as this variable equals true means that the algorithm has been implemented
    is_init = true;
}

//! Function to calculate Completion time
void RR::calcCompletionTime() {
    int len = getProcessesSize();
    
    //!Declare an array to store completion time for each process
    int *completionTime = new int[len];
    
    Process *processes = getProcesses();

    vector< pair <string, int> > timeLine;

    //!Declare an array to store CPU Burst for each process
    int cpuBurst[len];
    
    int lastTime = 0;
    int maxIndex = 0;
    vector<int> queue;
    
    //!Declare array to check if Process in Queue or not
    bool isInQ[len];
    for (int i = 1; i < len; i++) {
        isInQ[i] = false;
    }
    queue.push_back(0);
    isInQ[0] = true;

    int totalOverhead = 0;
    int maxCompletionTime = lastTime;

    //!To add in array <cpuBurst>
    for (int i = 0; i < len; i++) {
        cpuBurst[i] = processes[i].getCpuBurst();
    }

    if (processes->getArrivalTime() != 0) {
        timeLine.push_back(pair<string, int>("  ", processes->getArrivalTime()));
        lastTime = processes->getArrivalTime();
        maxCompletionTime = lastTime;
    }

   loop:
    
    //! if Queue is not Empty enter into to loop
    while (!queue.empty()) {
        int index = queue.front();
        
        /*!
           If burst time is smaller than or equal to 
           quantum. Last cycle for this process 
        */
        if (m_quantum < cpuBurst[index]) {
            if (getCS())
                timeLine.push_back(pair<string, int>("CS", lastTime + getCS()));

            lastTime += m_quantum + getCS();
            
            //!Calc remaining CPU Burst for process via subtracting quantum in each cycle.
            cpuBurst[index] -= m_quantum;
            
            totalOverhead += getCS();

            timeLine.push_back(pair<string, int>("P" + to_string(processes[index].getID()), lastTime));
        } else {
            if (getCS())
                timeLine.push_back(pair<string, int>("CS", lastTime + getCS()));

            lastTime += cpuBurst[index] + getCS();
            cpuBurst[index] = 0;
            completionTime[index] = lastTime;
            
            //!change max Completion time
            if (lastTime > maxCompletionTime) {
                maxCompletionTime = lastTime;
            }
            totalOverhead += getCS();

            timeLine.push_back(pair<string, int>("P" + to_string(processes[index].getID()), lastTime));
        }

        if (maxIndex < index) {
            maxIndex = index;
        }

        //!add the ready processes to queue
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
            timeLine.push_back(pair<string, int>("  ", lastTime));
            goto loop;
            //!jump to loop lable
        }

    }

    setTotalOverhead(totalOverhead);
    setMaxCompletionTime(maxCompletionTime);
    setCompletionTime(completionTime);
    setTimeLine(timeLine);
}
