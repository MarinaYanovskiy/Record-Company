#include "GroupList.h"

GroupList::GroupList() :
m_root(nullptr)
{}

GroupList::~GroupList()
{
    deleteList();
}

void GroupList::insert(Group *g)
{
    if(!m_root)
        m_root=g;
    else
    {
        g->setNext(m_root);
        m_root->setPrev(g);
        m_root =g;
    }
}

void GroupList::remove(Group *g)
{
    if(!m_root)
        return;

    if(m_root==g)
    {
        m_root=g->getNext();
        m_root->setPrev(nullptr);
    }
    else
    {
        Group *oldNext =g->getNext(), *oldPrev=g->getPrev();
        if(oldNext)
        {
            oldNext->setPrev(oldPrev);
            oldPrev->setNext(oldNext);
        }
        else
        {
            oldPrev->setNext(nullptr);
        }
    }
    delete g;
}

void GroupList::deleteList()
{
    if(!m_root)
        return;
    Group * temp;
    while (m_root->getNext())
    {
        temp=m_root;
        m_root=m_root->getNext();
        delete temp;
    }
    delete m_root;
    m_root= nullptr;
}