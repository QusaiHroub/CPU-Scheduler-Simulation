/*
 * This file is part of OS Project.
 *
 * Authors
 * Mohammad Abureesh
 * Qusai Hroub
 *
 */

#include "Process.hpp"
#include "ProcessManagement.hpp"

class RR : public ProcessManagement
{
public:
    RR();
    RR(Process* = nullptr, int = 0, int = 0, int = 5);
    ~RR();

private:
    bool is_init = false;
    
    int m_quantum;

    void init(int=0);


};

