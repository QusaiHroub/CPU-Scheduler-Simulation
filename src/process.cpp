/*
 * This file is part of OS Project.
 *
 * Authors
 * Qusai Hroub
 * Mohammad Abureesh
 *
 */

#include "process.h"

/*
This constructor receives process ID, arrival time, CPU burst, and size for each process.
size in bytes for each process, and Passing these values via <setters> 
*/
Process::Process(int id, int arrivalTime, int cpuBurst, int size) {
    setID(id);
    setArrivalTime(arrivalTime);
    setCPUBurst(cpuBurst);
    setSize(size);
}

//Default constructor
Process::Process() {}

//this function return id for process 
int Process::getID() {
    return m_id;
}

//this function return Arrival time for process 
int Process::getArrivalTime() {
    return m_arrivalTime;
}

//this function return CPU Burst for process 
int Process::getCpuBurst() {
    return m_cpuBurst;
}

//this function return size for process 
int Process::getSize() {
    return m_size;
}

//To change Process id
void Process::setID(int id) {
    m_id = id;
}

//To change Process arrival time
void Process::setArrivalTime(int arrivalTime) {
    m_arrivalTime = arrivalTime;
}

//To change Process CPU Burst
void Process::setCPUBurst(int cpuBurst) {
    m_cpuBurst = cpuBurst;
}

//To change Process Size
void Process::setSize(int size) {
    m_size = size;
}
