//
// Created by nrhbv on 09/06/2023.
//
#include "nodeInGroup.h"
 nodeInGroup::nodeInGroup():
m_father(nullptr),
m_group(nullptr),
m_record(),
m_extraForHightCalc(0),
m_hight(0)
 {}


 nodeInGroup::nodeInGroup(CDRecord record):
 m_father(nullptr),
 m_group(nullptr),
 m_record(record),
 m_extraForHightCalc(0),
 m_hight(record.getCopies())
 {}

void nodeInGroup::setFather(nodeInGroup *father)
{
     m_father=father;
}

nodeInGroup *nodeInGroup::getFather()
{
    return m_father;
}

Group *nodeInGroup::getGroup()
{
    return m_group;
}

void nodeInGroup::setGroup(Group *group)
{
     m_group = group;
}

int nodeInGroup::getExtraHight() const
{
    return m_extraForHightCalc;
}

void nodeInGroup::setExtra(int extra)
{
     m_extraForHightCalc=extra;
}