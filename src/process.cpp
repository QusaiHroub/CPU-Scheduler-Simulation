#include "process.h"

Process::Process(int arrivalTime, int cpuBurst, int size) {
    setArrivalTime(arrivalTime);
    setCPUBurst(cpuBurst);
    setSize(size);
}

Process::Process() {}

int Process::getArrivalTime() {
    return m_arrivalTime;
}

int Process::getCpuBurs() {
    return m_cpuBurst;
}

int Process::getSize() {
    return m_size;
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
