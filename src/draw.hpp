#ifndef DRAW_HPP
#define DRAW_HPP

#include <vector>

using namespace std;

class Draw {
public:
    Draw();

    void drawTable(vector<vector<int>> &);
    void drawAVGSTable(vector<double> &);
};

#endif // DRAW_HPP
