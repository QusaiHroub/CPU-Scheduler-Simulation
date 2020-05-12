#include <fstream>
#include <string>
#include <iostream>
#include "process.h"

using namespace std;

class ReadData {
private:
    string m_data;
    ifstream m_inFile;
    Process m_processes[5];
    int m_tempArr[24];
    int m_memSize;
    int m_pageSize;
    int m_quantum;
    int m_contextSwitch;

public:
    void openFile();
    void printFile();
    int readFile();
    void closeFile();
    Process *getProcesses();
    int getContextSwitch();
    int getQuantum();
    int getMemSize();
    int getFrameSize();
};
