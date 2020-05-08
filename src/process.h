#pragma once
#include<iostream>
using namespace std;
class Process
{
private:
    int m_arrivalTime;
    int m_cpuBurst;
    int m_size;   // size in Bytes
	
public:
	
    Process();
    Process(int, int, int);
	
    int getArrivalTime();
    int getCpuBurs();
    int getSize();

    void setArrivalTime(int);
    void setCPUBurst(int);
    void setSize(int);
};


