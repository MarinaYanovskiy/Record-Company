//
// Created by nrhbv on 09/06/2023.
//

#ifndef UNIONFIND_UNIONFIND_H
#define UNIONFIND_UNIONFIND_H

#include "CDRecord.h"
#include "Group.h"
#include "GroupList.h"
class UnionFind {
private:
    int m_numOfRecords;
    CDRecord* m_records;
    nodeInGroup** m_recordsMappedToGroups;
    GroupList m_groups;


public:
    UnionFind();
    ~UnionFind();
    void reset(int* record_stocks, int number_of_records);
    Group* Union(Group* source, Group* destination);
    Group* Find(int record) const;
    nodeInGroup* MakeSet(CDRecord record);
    CDRecord* getRecordInPlace(int n) const;
    int getColumn(int record) const;
    int getHight(int record) const;
};


#endif // UNIONFIND_UNIONFIND_H
