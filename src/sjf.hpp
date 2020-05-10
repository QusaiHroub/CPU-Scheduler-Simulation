/*
 * This file is part of OS Project.
 *
 * Authors
 * Mohammad Abureesh
 * Qusai Hroub
 *
 */

#include "process.h"
#include "processmanagement.hpp"

#include <iostream>
#include <vector>

using namespace std;

class SJF : public ProcessManagement{
public:
    SJF(Process * = nullptr, int = 0, int = 5);
    ~SJF();

private:
    bool is_init = false;
    vector<Process> m_readyQueue;
    bool *visited;

    void init();

    void calcCompletionTime();

    static bool comp(Process &, Process &);
    static bool compCPUBurst(Process &, Process &);
};
