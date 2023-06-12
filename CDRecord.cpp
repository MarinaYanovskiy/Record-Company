//
// Created by nrhbv on 09/06/2023.
//

#include "CDRecord.h"
CDRecord::CDRecord(int id, int copies) :
m_id(id),
m_copies(copies),
m_purchases(0)
{}

CDRecord::CDRecord() :
        m_id(-1),
        m_copies(0),
        m_purchases(0)
{}

void CDRecord::buyRecord()
{
    m_purchases++;
}

int CDRecord::getCopies() const
{
    return m_copies;
}

int CDRecord::getColumns() const
{
    return m_id;
}