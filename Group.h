//
// Created by nrhbv on 09/06/2023.
//

#ifndef UNIONFIND_GROUP_H
#define UNIONFIND_GROUP_H
#include "nodeInGroup.h"

class nodeInGroup;
class Group {
private:
    int m_column;
    int m_hight;
    nodeInGroup* m_base;
    int m_size;
    Group* m_prev;
    Group* m_next;


public:
    Group(int col, int hight, int size, nodeInGroup* node);
    int getColumn() const;
    void setColumn(int col);
    Group* merge(Group* other);
    void setNext(Group *group);
    void setPrev(Group *group);
    Group* getPrev();
    Group* getNext();
};


#endif //UNIONFIND_GROUP_H
