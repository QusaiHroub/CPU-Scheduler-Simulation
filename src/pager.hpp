#ifndef PAGER_HPP
#define PAGER_HPP

#include "pagetable.hpp"
#include "process.h"

class Pager {
    int m_memSize;
    int m_fSize;
    pair < bool *, int > m_memMap = pair < bool *, int > (nullptr, 0);
public:
    Pager();
    Pager(int, int);
    ~Pager();

    void init(int, int);
    pair<PageTable **, int> paging(Process *, int);
};

#endif // PAGER_HPP
