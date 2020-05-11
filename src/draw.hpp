#ifndef DRAW_HPP
#define DRAW_HPP

#include <vector>
#include <string>

using namespace std;

class Draw {
public:
    Draw();

    void drawTable(vector< pair < int *, int> > &);
    void drawAVGSTable(vector<double> &);
    void drawGANTTChart(vector<pair<string, int>> &);
};

#endif // DRAW_HPP
