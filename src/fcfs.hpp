/*
 * This file is part of OS Project.
 *
 * Authors
 * Qusai Hroub
 * 
 * C++ program for implementation of FCFS algorithm  
 * scheduling
 * this class inherits all characteristics in <ProcessManagement>
 */

#ifndef FCFS_HPP
#define FCFS_HPP

#include "process.h"
#include "processmanagement.hpp"

class FCFS : public ProcessManagement{
public:
 //constructors
    FCFS(Process * = nullptr, int = 0, int = 5);
    ~FCFS();

private:
    bool is_init = false;
    
 //Functions 
    
    //this Function initializes all function for algorithm
    void init();
    
    static bool comp(Process &, Process &);
};
#endif // FCFS_HPP
