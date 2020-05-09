#include "readData.h"

void ReadData::openFile() {
    m_inFile.open("processes.txt");
}

void ReadData::printFile() {
    for (int i = 0; i < 10; i++) {
        cout << m_tempArr[i] << endl;
    }
}

int ReadData::readFile() {
    //Read file
    bool is_try = false;
    tryFlag:
    if (m_inFile.is_open()) {
        int index = 0;

        while(m_inFile >> m_tempArr[index++]);

        m_phiysicalAddress = m_tempArr[0];
        m_pageSize = m_tempArr[1];
        m_roundRobin = m_tempArr[2];
        m_contextSwitch = m_tempArr[3];

        index = 0;
        for (int i = 4; i + 4 < 24; i += 4) {
            m_processes[index++] = Process(m_tempArr[i], m_tempArr[i + 1], m_tempArr[i + 2], m_tempArr[i + 3]);
        }
    // end read
    } else {
        if (is_try) {
            return -1;
        }
        is_try = true;
        openFile();
        goto tryFlag;
    }

    return 0;
}

void ReadData::closeFile() {
    m_inFile.close();
}

Process *ReadData::getProcesses() {
    return m_processes;
}

int ReadData::getContextSwitch() {
    return m_contextSwitch;
}
