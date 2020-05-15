/*!
 * This file is part of OS Project.
 *
 * Authors
 * Mohammad Abureesh
 * Qusai Hroub
 *
 * RR algorithm
 * scheduling
 * this class inherits all characteristics in <ProcessManagement>
 *
 */

#include "process.h"
#include "processmanagement.hpp"

class RR : public ProcessManagement
{
public:
 //!constructors
    RR(Process* = nullptr, int = 0, int = 5, int = 0);
    ~RR();

private:
    bool is_init = false;
    
    int m_quantum;

 //!Functions

    //!this Function initializes all function for algorithm
    void init(int = 0);

    void calcCompletionTime();

    //!this function return true if arrival time for first process less than arrival time for the second process.
    static bool comp(Process &, Process &);
};

