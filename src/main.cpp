
/*
 * This file is part of OS Project.
 *
 * Authors
 * Qusai Hroub
 * Mohammad Abureesh
 *
 */

#include <iostream>
#include <vector>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __linux__
#endif

#include "readData.h"
#include "process.h"
#include "fcfs.hpp"
#include "sjf.hpp"
#include "RR.hpp"
#include "draw.hpp"
#include "processmanagement.hpp"
#include "pagetable.hpp"
#include "pager.hpp"

using namespace std;

bool isProcessDef(int id, Process *processes, int len);

// Driver code 
int main()  {
#ifdef _WIN32
    HWND console = GetConsoleWindow();
    RECT rect;
    GetWindowRect(console, &rect);
    MoveWindow(console, rect.left, rect.top, 800, 400, TRUE);
#endif

#ifdef __linux__

#endif

    Draw draw;

    vector < ProcessManagement * > processManagementList;
    vector < string > processManagementListOfNames;
    vector < double > avgTable;
    vector< pair < int *, int> > table;

    ReadData r(5);

    r.openFile();
    if (r.readFile()) {
        cout << "Error occurred we can't read the Processes file." << endl;
        return -1;
    }
    r.closeFile();

    FCFS *fcfs = new FCFS(r.getProcesses(), r.getContextSwitch(), r.getProcessesLength());

    SJF *sjf = new SJF(r.getProcesses(), r.getContextSwitch(), r.getProcessesLength());

    RR *rr = new RR(r.getProcesses(), r.getContextSwitch(), r.getProcessesLength(), r.getQuantum());

    Pager pager(r.getMemSize(), r.getFrameSize());

    processManagementList.push_back(dynamic_cast<ProcessManagement *>(fcfs));
    processManagementListOfNames.push_back("FCFS");
    processManagementList.push_back(dynamic_cast<ProcessManagement *>(sjf));
    processManagementListOfNames.push_back("SJF");
    processManagementList.push_back(dynamic_cast<ProcessManagement *>(rr));
    processManagementListOfNames.push_back("RR");

    pair<PageTable **, int> pageTableList = pager.paging(r.getProcesses(), r.getProcessesLength());

    int ch;

    mainInputLoop:
    while (cout << "\n\t1.Part One\n \t2.Part two\n \t3.Exit.\n",
           cout << "\tSelect :",
           cin >> ch) {
        if (ch == 1) {
            for (size_t i = 0; i < processManagementList.size(); i++) {
                cout << endl << "\t" << processManagementListOfNames[i] << endl;
                avgTable.clear();
                avgTable.push_back(processManagementList[i]->avgWaitingTime());
                avgTable.push_back(processManagementList[i]->avgCompletionTime());
                avgTable.push_back(processManagementList[i]->avgTurnAroundTime());
                avgTable.push_back(processManagementList[i]->cpuUtilization());

                table.clear();
                table.push_back(pair<int *, int> (processManagementList[i]->getProcessesIDs(), r.getProcessesLength()));
                table.push_back(pair<int *, int> (processManagementList[i]->getProcessesArrivalTime(), r.getProcessesLength()));
                table.push_back(pair<int *, int> (processManagementList[i]->getProcessesBurstTime(), r.getProcessesLength()));
                table.push_back(pair<int *, int> (processManagementList[i]->getDeepCopyOfCompletionTime(), r.getProcessesLength()));
                table.push_back(pair<int *, int> (processManagementList[i]->getDeepCopyOfTurnAroundTime(), r.getProcessesLength()));
                table.push_back(pair<int *, int> (processManagementList[i]->getDeepCopyOfWaitingTime(), r.getProcessesLength()));

                draw.drawTable(table);
                draw.drawAVGSTable(avgTable);

                cout << endl;
                draw.drawGANTTChart(processManagementList[i]->getTimeLine());
            }
        } else if (ch == 2) {
            for (int i = 0; i < pageTableList.second; i++) {
                cout << endl;
                draw.drawPageTable(*pageTableList.first[i]);
            }

            cout << endl;
            draw.drawMemMap(pager.getMemMap());

            int logicalAddress, processID;
            while (cout << "\n\tEnter process ID and logicalAssress for mapping: ", cin >> processID >> logicalAddress) {
                while (!isProcessDef(processID, r.getProcesses(), r.getProcessesLength())) {
                    cout << "\tProcess " << processID << " not found, enter valid ID: ";
                    cin >> processID;
                }
                Pager::Address address = pager.mapping(processID, logicalAddress, pageTableList);
                while (address.errorCode == 1) {
                    cout << "\tEnter Valid address for process " << processID << ": ";
                    cin >> logicalAddress;
                    address = pager.mapping(processID, logicalAddress, pageTableList);
                }
                draw.drawPhysicalAddressMapingSeq(address);
            }
            goto mainInputLoop;
        } else {
            goto end;
        }
    }

    end:
    delete rr;
    delete sjf;
    delete fcfs;

    for (int i = 0; i < pageTableList.second; i++) {
        delete pageTableList.first[i];
    }
    delete pageTableList.first;

    return 0;
}

bool isProcessDef(int id, Process *processes, int len) {
    for (int i = 0; i < len; i++) {
        if (processes[i].getID() == id) {
            return true;
        }
    }

    return false;
}
