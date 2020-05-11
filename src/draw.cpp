#include "draw.hpp"

#include <iostream>
#include <iomanip>

Draw::Draw() {

}

void Draw::drawAVGSTable(vector<double> &table) {
    cout << fixed << setprecision(2);
    cout << "\t+-----------------------------+-----------+" << endl;
    cout << "\t| AVG of Waiting Time         |   " << setw(5) << table[0];
    cout << setw(4) << "|" << endl;
    cout << "\t+-----------------------------+-----------+" << endl;
    cout << "\t| AVG of Completion Time      |   " << setw(5) << table[1];
    cout << setw(4) << "|" << endl;
    cout << "\t+-----------------------------+-----------+" << endl;
    cout << "\t| AVG of Turn AroundTime Time |   " << setw(5) << table[2];
    cout << setw(4) << "|" << endl;
    cout << "\t+-----------------------------+-----------+" << endl;
    cout << "\t| CPU Utilization             |   " << setw(5) << table[3];
    cout << setw(4) << "|" << endl;
    cout << "\t+-----------------------------+-----------+" << endl;
}

void Draw::drawTable(vector< pair < int *, int> > &table) {
    cout << "\t+--------------+----------------+--------------+-------------------+--------------------+----------------+" << endl;
    cout << "\t|  Process ID  |  Arrival Time  |  Burst Time  |  Completion Time  |  Turn Around Time  |  Waiting Time  |" << endl;
    cout << "\t+--------------+----------------+--------------+-------------------+--------------------+----------------+" << endl;

    for (int i = 0; i < table[0].second; i++) {
        cout << "\t|      " << setw(2) << "p" + to_string(table[0].first[i]) << "      |       "
             << setw(2) << to_string(table[1].first[i]) << "       |      "
             << setw(2) << to_string(table[2].first[i]) << "      |         "
             << setw(2) << to_string(table[3].first[i]) << "        |         "
             << setw(2) << to_string(table[4].first[i]) << "         |       "
             << setw(2) << to_string(table[5].first[i]) << "       |";
        cout << "\n\t+--------------+----------------+--------------+-------------------+--------------------+----------------+" << endl;
    }
}
