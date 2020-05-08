#include "process.h"

Process::Process(int id, int arrivalTime, int cpuBurst, int size) {
    setID(id);
    setArrivalTime(arrivalTime);
    setCPUBurst(cpuBurst);
    setSize(size);
}

Process::Process() {}

int Process::getID() {
    return m_id;
}

int Process::getArrivalTime() {
    return m_arrivalTime;
}

int Process::getCpuBurs() {
    return m_cpuBurst;
}

int Process::getSize() {
    return m_size;
}

void Process::setID(int id) {
    m_id = id;
}

void Process::setArrivalTime(int arrivalTime) {
    m_arrivalTime = arrivalTime;
}
void Process::setCPUBurst(int cpuBurst) {
    m_cpuBurst = cpuBurst;
}
void Process::setSize(int size) {
    m_size = size;
}
