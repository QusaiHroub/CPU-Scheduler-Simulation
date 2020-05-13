/*
 * This file is part of OS Project.
 *
 * Authors
 * Qusai Hroub
 * 
 * Draw tables for part one and part two in this project.
 * this file, declaration for "draw.hpp".
 *
 */

#include "draw.hpp"

#include <iostream>
#include <iomanip>

//Default constructor.
Draw::Draw() {

}

//To draw averages table for each algorithm in this program.
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

//To draw table for all processes, and it contains all info for each process
void Draw::drawTable(vector< pair < int *, int> > &table) {
    cout << "\t+--------------+----------------+--------------+-------------------+--------------------+----------------+" << endl;
    cout << "\t|  Process ID  |  Arrival Time  |  Burst Time  |  Completion Time  |  Turn Around Time  |  Waiting Time  |" << endl;
    cout << "\t+--------------+----------------+--------------+-------------------+--------------------+----------------+" << endl;

    for (int i = 0; i < table[0].second; i++) {
        cout << "\t|      " << setw(2) << "P" + to_string(table[0].first[i]) << "      |       "
             << setw(2) << to_string(table[1].first[i]) << "       |      "
             << setw(2) << to_string(table[2].first[i]) << "      |         "
             << setw(2) << to_string(table[3].first[i]) << "        |         "
             << setw(2) << to_string(table[4].first[i]) << "         |       "
             << setw(2) << to_string(table[5].first[i]) << "       |";
        cout << "\n\t+--------------+----------------+--------------+-------------------+--------------------+----------------+" << endl;
    }
}


//To draw Gant chart for each algorithm in this program.
void Draw::drawGANTTChart(vector<pair<string, int> > &timeLine) {
    cout << "\tGANTT Chart" << endl;
    cout << "\t+";
    for (size_t i = 0; i < timeLine.size(); i++) {
        cout << "------+";
    }
    cout << endl;

    cout << "\t|";
    for (size_t i = 0; i < timeLine.size(); i++) {
        cout << "  " + timeLine[i].first + "  |";
    }
    cout << endl;

    cout << "\t+";
    for (size_t i = 0; i < timeLine.size(); i++) {
        cout << "------+";
    }
    cout << endl;

    cout << "\t0";
    for (size_t i = 0; i < timeLine.size(); i++) {
        cout << setw(7) << timeLine[i].second;
    }
    cout << endl;
}

//To draw Page table for use in part two
void Draw::drawPageTable(PageTable &pageTable) {
    int len = pageTable.getLength();
    PageTable::tableElement *table = pageTable.getTable();
    string stat1, stat2;
    cout << "\t+--------------------------+" << endl;
    cout << "\t|    Page Table for P" << setw(2) << pageTable.getProcessID() << "    |" << endl;
    cout << "\t+------------+-------------+-----------+-------------+" << endl;
    cout << "\t|  Page No.  |  Frame No.  | Is valid  |  Is in mem  |" << endl;
    cout << "\t+------------+-------------+-----------+-------------+" << endl;

    for (int i = 0; i < len; i++) {
        if (table[i].isValid) {
            stat1 = "YES";
            if (table[i].isInMem) {
                stat2 = "YES";
            } else {
                stat2 = " NO";
            }
        } else {
            stat1 = " NO";
            stat2 = "---";
        }
        cout << "\t|    " << setw(3) << i << "     |     " << setw(3) << table[i].fNumber
             << "     |    " << stat1 << "    |     " << stat2 << "     |\n";
        cout << "\t+------------+-------------+-----------+-------------+" << endl;
    }
}


//To draw memory Map for use in part two 
void Draw::drawMemMap(pair<pair<bool *, int>, pair<int, int> *> &memMap) {
    string stat1 = "NULL", stat2 = "---", stat3 = "---";
    int len = memMap.first.second;
    bool *isAllco = memMap.first.first;
    pair<int, int> * pId_pageNo = memMap.second;

    cout << "\t+--------------+" << endl;
    cout << "\t|  Memory map  |\n";
    cout << "\t+--------------+----------------+-------+------------+" << endl;
    cout << "\t|   Frame No.  |  Is allocated  |  PID  |  Page No.  |" << endl;
    cout << "\t+--------------+----------------+-------+------------+" << endl;
    cout << "\t|     " << setw(3) << 0 << "      |       " << stat1 << "     |  " << stat2 << "  |    " << stat3 << "     |" << endl;
    cout << "\t+--------------+----------------+-------+------------+" << endl;

    for (int i = 1; i < len; i++) {
        if (isAllco[i]) {
            stat1 = "YES";
            if (pId_pageNo[i].first == -1) {
                stat2 = "OS";
                stat3 = "---";
            } else {
                stat2 = to_string(pId_pageNo[i].first);
                stat3 = to_string(pId_pageNo[i].second);
            }
        } else {
            stat1 = " NO";
            stat2 = stat3 = "---";
        }

        cout << "\t|     " << setw(3) << i << "      |       " << stat1 << "      |  " << setw(3) << stat2 << "  |    " << setw(3) << stat3 << "     |" << endl;
        cout << "\t+--------------+----------------+-------+------------+" << endl;
    }
}

//To draw Physical Address Maping for use in part two
void Draw::drawPhysicalAddressMapingSeq(Pager::Address &address) {
    cout << "\tPhysical address is " << address.logicalAndPhysicalAddress.second << endl;
    cout << "\t" << address.logicalAndPhysicalAddress.first << " ---> (p, d) = ("
         << address.pd.first << ", " << address.pd.second << ") ---> (f, d) = ("
         << address.fd.first << ", " << address.fd.second << ") ---> " << address.logicalAndPhysicalAddress.second << endl;
}
