//
// Created by nrhbv on 09/06/2023.
//

#ifndef UNIONFIND_NODEINGROUP_H
#define UNIONFIND_NODEINGROUP_H

#include "CDRecord.h"
#include "Group.h"
class Group;

class nodeInGroup {
private:
nodeInGroup* m_father;
Group* m_group;
CDRecord m_record;
int m_extraForHightCalc;
int m_hight;


public:
    nodeInGroup();
    nodeInGroup(CDRecord record);
    void setFather(nodeInGroup* father);
    nodeInGroup* getFather();
    Group* getGroup();
    void setGroup(Group* group);
    int getExtraHight() const;
    void setExtra(int extra);
};


#endif //UNIONFIND_NODEINGROUP_H
