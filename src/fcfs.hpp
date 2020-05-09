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

class FCFS {
public:
    FCFS();
    FCFS(Process * = nullptr, int = 0, int = 5);
    ~FCFS();

    int *turnAroundTime();
    double avgWaitingTime();
    int *getDeepCopyOfWaitingTime();

private:
    const int PROCESSES_SIZE;

    Process *m_processes = nullptr;
    int m_CS;
    bool is_init = false;

    int *m_waitingTime = nullptr;

    void init(Process * = nullptr, int = 0);
};

#endif // FCFS_HPP
