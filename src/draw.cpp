#include "draw.hpp"

#include <iostream>
#include <iomanip>

Draw::Draw() {

}

void Draw::drawAVGSTable(vector<double> &table) {
    cout << fixed << setprecision(2);
    cout << "\t+-----------------------------+---------+" << endl;;
    cout << "\t| AVG of Waiting Time         | " << setw(5) << table[0];
    cout << setw(4) << "|" << endl;
    cout << "\t+-----------------------------+---------+" << endl;
    cout << "\t| AVG of Completion Time      | " << setw(5) << table[1];
    cout << setw(4) << "|" << endl;
    cout << "\t+-----------------------------+---------+" << endl;
    cout << "\t| AVG of Turn AroundTime Time | " << setw(5) << table[2];
    cout << setw(4) << "|" << endl;
    cout << "\t+-----------------------------+---------+" << endl;
    cout << "\t| CPU Utilization             | " << setw(5) << table[3];
    cout << setw(4) << "|" << endl;
    cout << "\t+-----------------------------+---------+" << endl;
}

void Draw::drawTable(vector<vector<int> > &table) {

}
