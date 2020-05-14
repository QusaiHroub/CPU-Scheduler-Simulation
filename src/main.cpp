
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
#include <algorithm>

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

Process *isProcessDef(int id, Process *processes, int len);

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

    Pager pager(r.getProcesses(), r.getProcessesLength(), r.getMemSize(), r.getFrameSize());

    processManagementList.push_back(dynamic_cast<ProcessManagement *>(fcfs));
    processManagementListOfNames.push_back("FCFS");
    processManagementList.push_back(dynamic_cast<ProcessManagement *>(sjf));
    processManagementListOfNames.push_back("SJF");
    processManagementList.push_back(dynamic_cast<ProcessManagement *>(rr));
    processManagementListOfNames.push_back("RR");

    PageTable *pageTable = nullptr;
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
            part2menu:
            while (cout << "\n\n\t1. allocate process by its ID\n\t2. deallocate process by its ID",
                   cout << "\n\t3. reallocate process by its ID\n\t4. print page tabel for process",
                   cout << "\n\t5. print memory map\n\t6. maping logical address to phyiscal\n\t7. return to main menu\n\tselect: ",
                    cin >> ch) {
                if (ch == 1) {
                    cout << "\tEnter Process ID: ";
                    int id;
                    Process *p;
                    while (cin >> id, p = isProcessDef(id, r.getProcesses(), r.getProcessesLength()), p == nullptr) {
                        cout << "\tEnter valid ID: ";
                    }
                    draw.drawPageTable(*pager.palloc(p));
                } else if (ch == 2) {
                    cout << "\tEnter Process ID: ";
                    int id;
                    Process *p;
                    while (cin >> id, p = isProcessDef(id, r.getProcesses(), r.getProcessesLength()), p == nullptr) {
                        cout << "\tEnter valid ID: ";
                    }
                    pager.free(p);
                    cout << "process " << id << " is free from the memory." << endl;
                } else if (ch == 3) {
                    cout << "\tEnter Process ID: ";
                    int id;
                    Process *p;
                    while (cin >> id, p = isProcessDef(id, r.getProcesses(), r.getProcessesLength()), p == nullptr) {
                        cout << "\tEnter valid ID: ";
                    }
                    PageTable *pageT = pager.prealloc(p);
                    if (pageT == nullptr) {
                        cout << "You cant reallocat not allocated process." << endl;
                    } else {
                        draw.drawPageTable(*pageT);
                    }
                } else if (ch == 4) {
                    cout << "\tEnter Process ID: ";
                    int id;
                    Process *p;
                    while (cin >> id, p = isProcessDef(id, r.getProcesses(), r.getProcessesLength()), p == nullptr) {
                        cout << "\tEnter valid ID: ";
                    }
                    if (p->getPageTable() == nullptr) {
                        cout << "\tProcess with ID = " << id << " is not have page table, do you want to yes it? (YES, NO): ";
                        string input;
                        cin >> input;
                        transform(input.begin(), input.end(), input.begin(),
                            [](unsigned char c){ return std::tolower(c); });
                        if (input == "yes") {
                            pager.palloc(p);
                            pager.free(p);
                            cout << input << endl;
                        }
                    }
                    draw.drawPageTable(*p->getPageTable());
                } else if (ch == 5) {
                    draw.drawMemMap(pager.getMemMap());
                } else if (ch == 6) {
                    int logicalAddress, processID;
                    while (cout << "\n\tEnter process ID and logical address for mapping (enter -1 to return to menu): ", cin >> processID) {
                        if (processID == -1) {
                            goto part2menu;
                        }
                        cin >> logicalAddress;
                        Process *process;
                        while (process = isProcessDef(processID, r.getProcesses(), r.getProcessesLength()), process == nullptr) {
                            cout << "\tProcess " << processID << " not found, enter valid ID: ";
                            cin >> processID;
                        }
                        Pager::Address address = pager.mapping(*process, logicalAddress);
                        if (address.errorCode == 1) {
                            cout << "\tProcess with ID = " << processID << " is not allocated do you want to allocate it? (YES, NO): ";
                            string input;
                            cin >> input;
                            transform(input.begin(), input.end(), input.begin(),
                                [](unsigned char c){ return std::tolower(c); });
                            if (input == "yes") {
                                pager.palloc(process);
                                address = pager.mapping(*process, logicalAddress);
                            } else {
                                continue;
                            }
                        }
                        while (address.errorCode == 2) {
                            cout << "\tEnter Valid address for process " << processID << ": ";
                            cin >> logicalAddress;
                            address = pager.mapping(*process, logicalAddress);
                        }
                        draw.drawPhysicalAddressMapingSeq(address);
                    }
                } else if (ch == 7) {
                    goto mainInputLoop;
                }
            }
        } else {
            goto end;
        }
    }

    end:
    delete rr;
    delete sjf;
    delete fcfs;
    if (!pageTable) {
        delete pageTable;
    }

    return 0;
}

Process *isProcessDef(int id, Process *processes, int len) {
    for (int i = 0; i < len; i++) {
        if (processes[i].getID() == id) {
            return &processes[i];
        }
    }

    return nullptr;
}
