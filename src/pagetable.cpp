/*
 * This file is part of OS Project.
 *
 * Authors
 * Qusai Hroub
 *
 */

#include "pagetable.hpp"

PageTable::PageTable(int processID, tableElement *table, int len) {
    if (processID == -1 || !table || len < 1) {
        return;
    }

    init(processID, table, len);
}

//deconstructor
PageTable::~PageTable() {
    if (m_table) {
        delete m_table;
    }
}

//To implements PagerTable
void PageTable::init(int processID, tableElement *table, int len) {
    if (processID == -1 || !table || len < 1) {
        return;
    }
    m_processID = processID;
    m_table = table;
    m_length = len;
}

/*
    This function return  array <m_table> of type tableElement. 
    tableElement is <struct> .
*/
PageTable::tableElement *PageTable::getTable() {
    return m_table;
}

//To return length 
int PageTable::getLength() {
    return m_length;
}

//To return Process id 
int PageTable::getProcessID() {
    return m_processID;
}
