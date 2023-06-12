//
// Created by nrhbv on 09/06/2023.
//

#ifndef UNIONFIND_CDRECORD_H
#define UNIONFIND_CDRECORD_H


class CDRecord {
private:
    int m_id;
    int m_copies;
    int m_purchases;

public:
    CDRecord();
    CDRecord(int id, int copies);
    void buyRecord();
    int getColumns() const;
    int getCopies() const;
    int getPrice() const;
};


#endif // UNIONFIND_CDRECORD_H
