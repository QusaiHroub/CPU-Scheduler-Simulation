/*
 * This file is part of OS Project.
 *
 * Authors
 * Qusai Hroub
 * Mohammad Abureesh
 *
 * C++ program for read all requirements we needed in this program from text file.
 * this file, declaration for "readData.hpp"
 */

#include "readData.hpp"


//To Open file <processes.txt>
void ReadData::openFile() {
    m_inFile.open("processes.txt");
}

//To print file after store Data in array <m_tempArr>
void ReadData::printFile() {
    for (int i = 0; i < 10; i++) {
        cout << m_tempArr[i] << endl;
    }
}


/*
To read the file and add all needed data into array <m_tempArr>.
these data required in the Program for use in all algorithms.
*/
int ReadData::readFile() {
    //Read file
    bool is_try = false;
    tryFlag:
    if (m_inFile.is_open()) {
        int index = 0;
        
        //To add all data in array <m_tempArr>
        while(m_inFile >> m_tempArr[index++]);

        //Physical memory size
        m_memSize = m_tempArr[0];
        
        //Page size or Frame Size, used for Pagger algorithm.
        m_pageSize = m_tempArr[1];
        
        //Quantum, used for Round Robin algorithm.
        m_quantum = m_tempArr[2];
        
        //cContext Switch , used for all algorithms.
        m_contextSwitch = m_tempArr[3];

        int sizeOfm_tempArr = index;
        index = 0;
        
       /*
        To add all processes into array <m processes>
        with each process add (process Id, arrival time, CPU Burst, and size)
       */
        for (int i = 4; i + 4 < sizeOfm_tempArr; i += 4) {
            m_processes[index++] = Process(m_tempArr[i], m_tempArr[i + 1], m_tempArr[i + 2], m_tempArr[i + 3]);
        }
    // end read
    } else {
        // terminate with error
        if (is_try) {
            return -1;
        }
        is_try = true;
        openFile();
        goto tryFlag;
    }

    return 0;
}

//To close file
void ReadData::closeFile() {
    m_inFile.close();
}

//This function return an array of processes
Process *ReadData::getProcesses() {
    return m_processes;
}

//To return Context Swithc
int ReadData::getContextSwitch() {
    return m_contextSwitch;
}

//To return Quantum
int ReadData::getQuantum() {
    return m_quantum;
}

//To return Physical memory size
int ReadData::getMemSize() {
    return m_memSize;
}

//To return Page Size or Frame Size
int ReadData::getFrameSize() {
    return m_pageSize;
}
