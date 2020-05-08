#include <iostream>
#include "readData.h"
#include "operations.h"
#include "process.h"

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

    op.WaitingTime_FCFS(r.getProcesses());
    op.TurnAroundTime_FCFS(r.getProcesses());

    cout << "Average waiting Time = " << op.AvgWaitingTime_FCFS() << endl;
    return 0;
}
