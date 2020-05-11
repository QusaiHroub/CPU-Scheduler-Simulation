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

class RR : public ProcessManagement
{
public:
    RR(Process* = nullptr, int = 0, int = 5, int = 0);
    ~RR();

private:
    bool is_init = false;
    
    int m_quantum;

    void init(int=0);

    void calcCompletionTime();

    static bool comp(Process &, Process &);
};

