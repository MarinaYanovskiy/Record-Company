
#include "Group.h"
Group::Group(int col, int hight, int size, nodeInGroup* node)
    : m_column(col)
    , m_hight(hight)
    , m_base(node)
    , m_size(size)
    , m_prev(nullptr)
    , m_next(nullptr)
{
}

Group* Group::getNext()
{
    return m_next;
}

Group* Group::getPrev()
{
    return m_prev;
}

void Group::setNext(Group* group)
{
    m_next = group;
}

void Group::setPrev(Group* group)
{
    m_prev = group;
}

int Group::getColumn() const
{
    return m_column;
}


Group* Group::merge(Group* other)
{
    if (other == this) {
        return nullptr;
    }

    if (m_size < other->m_size) {
        other->m_base->setExtra(other->m_base->getExtraHight() + m_hight);
        m_base->setExtra(m_base->getExtraHight() - other->m_base->getExtraHight());

        m_base->setFather(other->m_base);
        Group* current = m_base->getGroup();
        m_base->setGroup(nullptr);
        other->m_base->setGroup(current);
        m_base = other->m_base;
    } else {
        other->m_base->setExtra(other->m_base->getExtraHight() + m_hight - m_base->getExtraHight());

        other->m_base->setFather(m_base);
        other->m_base->setGroup(nullptr);
    }
    m_size += other->m_size;
    m_hight += other->m_hight;
    return this;
}
