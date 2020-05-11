#pragma once
#include<iostream>
using namespace std;
class Process
{
private:
    int m_arrivalTime;
    int m_cpuBurst;
    int m_size;   // size in Bytes
    int m_id;
	
public:
	
    Process();
    Process(int, int, int, int);
	
    int getArrivalTime();
    int getCpuBurst();
    int getSize();
    int getID();

    void setArrivalTime(int);
    void setCPUBurst(int);
    void setSize(int);
    void setID(int);
};


