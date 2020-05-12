/*
 * This file is part of OS Project.
 *
 * Authors
 * Qusai Hroub
 * Mohammad Abureesh
 *
 * C++ program for Create Process
 * 
 */

#pragma once
#include<iostream>
using namespace std;

class Process
{
private:

    //Attributes for each process			
    int m_arrivalTime;
    int m_cpuBurst;
	
    // size in Bytes		
    int m_size;   
    int m_id;
    //end attributes		

public:
    
    //Constructor 	 
    Process();
    Process(int, int, int, int);

    //getters and setters
	
    int getArrivalTime();
    int getCpuBurst();
    int getSize();
    int getID();

    void setArrivalTime(int);
    void setCPUBurst(int);
    void setSize(int);
    void setID(int);
};


