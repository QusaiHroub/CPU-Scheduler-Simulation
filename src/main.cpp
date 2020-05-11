#include <iostream>
#include <vector>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __linux__
#endif

#include "readData.h"
#include "operations.h"
#include "process.h"
#include "fcfs.hpp"
#include "sjf.hpp"
#include "RR.hpp"
#include "draw.hpp"
#include "processmanagement.hpp"

using namespace std;

int main()  {
#ifdef _WIN32
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 800, 400, TRUE);
#endif

#ifdef __linux__

#endif

    Draw draw;

    vector < ProcessManagement * > processManagementList;
    vector < string > processManagementListOfNames;
    vector < double > avgTable;
    vector< pair < int *, int> > table;

    int ch;
    cout << "\n\t1.Part One\n \t2.Part two\n \t3.Exit.\n";
    cout << "\tSelect :";
    cin >> ch;
    cout<<endl<<endl;

    ReadData r;
    Process p;
    Operations op;

    r.openFile();
    if (r.readFile()) {
        cout << "Error occurred we can't read the Processes file." << endl;
        return -1;
    }
    r.closeFile();

    FCFS *fcfs = new FCFS(r.getProcesses(), r.getContextSwitch());

    SJF *sjf = new SJF(r.getProcesses(), r.getContextSwitch());

    RR *rr = new RR(r.getProcesses(), r.getContextSwitch(), 5, r.getQuantum());

    processManagementList.push_back(dynamic_cast<ProcessManagement *>(fcfs));
    processManagementListOfNames.push_back("FCFS");
    processManagementList.push_back(dynamic_cast<ProcessManagement *>(sjf));
    processManagementListOfNames.push_back("SJF");
    processManagementList.push_back(dynamic_cast<ProcessManagement *>(rr));
    processManagementListOfNames.push_back("RR");

    for (size_t i = 0; i < processManagementList.size(); i++) {
        cout << endl << "\t" << processManagementListOfNames[i] << endl;
        avgTable.clear();
        avgTable.push_back(processManagementList[i]->avgWaitingTime());
        avgTable.push_back(processManagementList[i]->avgCompletionTime());
        avgTable.push_back(processManagementList[i]->avgTurnAroundTime());
        avgTable.push_back(processManagementList[i]->cpuUtilization());

        table.clear();
        table.push_back(pair<int *, int> (processManagementList[i]->getProcessesIDs(), 5));
        table.push_back(pair<int *, int> (processManagementList[i]->getProcessesArrivalTime(), 5));
        table.push_back(pair<int *, int> (processManagementList[i]->getProcessesBurstTime(), 5));
        table.push_back(pair<int *, int> (processManagementList[i]->getDeepCopyOfCompletionTime(), 5));
        table.push_back(pair<int *, int> (processManagementList[i]->getDeepCopyOfTurnAroundTime(), 5));
        table.push_back(pair<int *, int> (processManagementList[i]->getDeepCopyOfWaitingTime(), 5));

        draw.drawTable(table);
        draw.drawAVGSTable(avgTable);

        cout << endl;
        draw.drawGANTTChart(processManagementList[i]->getTimeLine());
    }

    delete rr;
    delete sjf;
    delete fcfs;

    return 0;
}
