/*!
 * This file is part of OS Project.
 *
 * Authors
 * Qusai Hroub
 * 
 * Class Draw
 * used to draw tables for part one and part two in this project.
 * 
 */

#ifndef DRAW_HPP
#define DRAW_HPP

#include <vector>
#include <string>

#include "pagetable.hpp"
#include "pager.hpp"

using namespace std;

class Draw {
public:
    
    //!Constructor
    Draw();

    //!Functions
    void drawTable(vector< pair < int *, int> > &);
    void drawAVGSTable(vector<double> &);
    void drawGANTTChart(vector<pair<string, int>> &);
    void drawPageTable(PageTable &);
    void drawMemMap(pair < pair < bool *, int >, pair< int, int > *> &);
    void drawPhysicalAddressMapingSeq(Pager::Address &);
};

#endif //! DRAW_HPP
