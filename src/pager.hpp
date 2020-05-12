#ifndef PAGER_HPP
#define PAGER_HPP

#include "pagetable.hpp"
#include "process.h"

#include <map>

class Pager {
    int m_memSize;
    int m_fSize;
    pair < pair < bool *, int >, pair< int, int > *> m_memMap =
            pair < pair < bool *, int >, pair< int, int > *>(pair < bool *, int > (nullptr, 0), nullptr);
    map <int, int> m_processMap;
public:
    Pager();
    Pager(int, int);
    ~Pager();

    struct Address{
        pair <int, int> pd;
        pair <int, int> fd;
        pair <int, int> logicalAndPhysicalAddress;
        int errorCode;
    };

    void init(int, int);
    pair<PageTable **, int> paging(Process *, int);

    pair < pair < bool *, int >, pair< int, int > *> & getMemMap();
    Address mapping(int, int, pair<PageTable **, int> &);
};

#endif // PAGER_HPP
