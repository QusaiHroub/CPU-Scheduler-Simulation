/*
 * This file is part of OS Project.
 *
 * Authors
 * Qusai Hroub
 *
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
    
    //Methods
    void init();
    static bool comp(Process &, Process &);
};
#endif // FCFS_HPP
