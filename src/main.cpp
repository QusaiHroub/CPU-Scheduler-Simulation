#include <iostream>
#include "readData.h"
#include "operations.h"
#include "process.h"
#include "fcfs.hpp"
#include "sjf.hpp"

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

    cout << "Average waiting Time = " << fcfs.avgWaitingTime() << endl;
    return 0;
}
