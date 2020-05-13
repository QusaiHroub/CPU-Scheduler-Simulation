/*
 * This file is part of OS Project.
 *
 * Authors
 * Qusai Hroub
 * Mohammad Abureesh
 *
 * read text file.
 * 
 */

#include <fstream>
#include <string>
#include <iostream>
#include "process.h"

using namespace std;

class ReadData {
private:
    const int PROCESSES_LENGTH;

    //Attributes
    string m_data;
    ifstream m_inFile;
    
    //Declare an array of process, for using these processes in all algorithms in this program 
    Process *m_processes;
    
    //To put all data in this array, when use function readFile().
    int *m_tempArr;
    
    int m_memSize;
    int m_pageSize;
    
    // quantum for round robin algorithm
    int m_quantum;
    int m_contextSwitch;
    //end Attributes.

public:

    ReadData(int = 5);
    ~ReadData();
    
//Functions

    void openFile();
    void printFile();
    int readFile();
    void closeFile();
    
    //To return  array of Processes
    Process *getProcesses();

    int getProcessesLength();
    int getContextSwitch();
    int getQuantum();
    int getMemSize();
    int getFrameSize();
};
