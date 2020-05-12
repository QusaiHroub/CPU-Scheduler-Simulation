/*
 * This file is part of OS Project.
 *
 * Authors
 * Mohammad Abureesh
 * Qusai Hroub
 *
 * C++ program for implementation of SJF algorithm  
 * scheduling
 * this class inherits all characteristics in <ProcessManagement>
 */

#include "process.h"
#include "processmanagement.hpp"

#include <iostream>
#include <vector>

using namespace std;

class SJF : public ProcessManagement{
public:
  //constructors 
    SJF(Process * = nullptr, int = 0, int = 5);
    ~SJF();

private:
    bool is_init = false;
    vector<Process> m_readyQueue;
    bool *visited;

 //Functions 
    
    //this Function initializes all function for algorithm
    void init();

    void calcCompletionTime();
    
    static bool comp(Process &, Process &);
    static bool compCPUBurst(Process &, Process &);
};
