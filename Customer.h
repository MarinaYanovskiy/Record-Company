//
// Created by nrhbv on 09/06/2023.
//

#ifndef HASH_CUSTOMER_H
#define HASH_CUSTOMER_H


class Customer {
private:
    int m_id;
    int m_phone;
    bool m_is_member;
    int m_monthly_expenses;

public:
    Customer(int c_id, int phone);
    int getId() const;
    int getPhone() const;
    void joinClub();
    void buyCD(int price);
    bool isMember() const;
    int getExpenses() const;
    void setExpenses(int expense);
};


#endif // HASH_CUSTOMER_H
