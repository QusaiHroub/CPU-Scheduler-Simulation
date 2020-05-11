#include <iostream>
#include "readData.h"
#include "operations.h"
#include "process.h"
#include "fcfs.hpp"
#include "sjf.hpp"
#include "RR.hpp"

using namespace std;

int main()  {
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

    FCFS fcfs(r.getProcesses(), r.getContextSwitch());

    SJF sjf(r.getProcesses(), r.getContextSwitch());

    RR rr(r.getProcesses(), r.getContextSwitch(), 5, r.getQuantum());

    cout << "Average waiting Time (SJF) = " << sjf.avgWaitingTime() << endl;
    cout << "CPU Utiliztion (SJF) = " << sjf.cpuUtilization() << endl;

    cout << "Average waiting Time (FCFS) = " << fcfs.avgWaitingTime() << endl;
    cout << "CPU Utiliztion (FCFS) = " << fcfs.cpuUtilization() << endl;

    cout << "Average waiting Time (RR) = " << rr.avgWaitingTime() << endl;
    cout << "CPU Utiliztion (RR) = " << rr.cpuUtilization() << endl;

    return 0;
}
