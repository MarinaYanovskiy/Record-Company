//
// Created by nrhbv on 09/06/2023.
//

#include "Customer.h"

Customer::Customer(int c_id, int phone):
m_id(c_id),
m_phone(phone),
m_is_member(false),
m_monthly_expenses(0)
{}

int Customer::getPhone() const
{
    return m_phone;
}

int Customer::getId() const
{
    return m_id;
}

void Customer::buyCD(int price)
{
    m_monthly_expenses+=price;
}

int Customer::getExpenses() const
{
    return m_monthly_expenses;
}

void Customer::joinClub()
{
    m_is_member = true;
}

bool Customer::isMember() const
{
    return m_is_member;
}

void Customer::setExpenses(int expense) {
    m_monthly_expenses = expense;
}
