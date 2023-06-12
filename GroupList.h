//
// Created by nrhbv on 09/06/2023.
//

#ifndef UNIONFIND_GROUPLIST_H
#define UNIONFIND_GROUPLIST_H

#include "Group.h"
class GroupList {
private:
    Group* m_root;

public:
    GroupList();
    ~GroupList();
    void insert(Group *g);
    void remove(Group *g);
    void deleteList();
};


#endif //UNIONFIND_GROUPLIST_H
