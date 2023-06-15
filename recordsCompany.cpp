#include "recordsCompany.h"

RecordsCompany::RecordsCompany()
{
}

RecordsCompany::~RecordsCompany()
{
}

StatusType RecordsCompany::newMonth(int* records_stocks, int number_of_records)
{
    if (number_of_records < 0) {
        return StatusType::INVALID_INPUT;
    }

    try {
        this->m_records.reset(records_stocks, number_of_records);
        for (auto member : m_clubMembers) {
            member->setExpenses(0);
        }
        m_clubMembers.resetExtra();

        return StatusType::SUCCESS;
    } catch (std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    }
}


StatusType RecordsCompany::addCostumer(int c_id, int phone)
{
    if (c_id < 0 || phone < 0) {
        return StatusType::INVALID_INPUT;
    }

    if (m_customers.find(c_id)) {
        return StatusType::ALREADY_EXISTS;
    }

    try {
        auto new_customer = std::make_shared<Customer>(c_id, phone);
        m_customers.insert(c_id, new_customer);
        return StatusType::SUCCESS;

    } catch (std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    }
}


Output_t<int> RecordsCompany::getPhone(int c_id)
{
    if (c_id < 0) {
        return StatusType::INVALID_INPUT;
    }

    auto customer = m_customers.find(c_id);
    if (customer == nullptr) {
        return StatusType::DOESNT_EXISTS;
    }

    return Output_t<int>(customer->getPhone());
}


StatusType RecordsCompany::makeMember(int c_id)
{
    if (c_id < 0) {
        return StatusType::INVALID_INPUT;
    }

    auto customer = m_customers.find(c_id);
    if (customer == nullptr) {
        return StatusType::DOESNT_EXISTS;
    }

    if (customer->isMember()) {
        return StatusType::ALREADY_EXISTS;
    }

    try {
        customer->joinClub();
        m_clubMembers.insert(c_id, customer);
        return StatusType::SUCCESS;
    } catch (std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    }
}


Output_t<bool> RecordsCompany::isMember(int c_id)
{
    if (c_id < 0) {
        return StatusType::INVALID_INPUT;
    }

    auto customer = m_customers.find(c_id);
    if (customer == nullptr) {
        return StatusType::DOESNT_EXISTS;
    }

    return Output_t<bool>(customer->isMember());
}

StatusType RecordsCompany::buyRecord(int c_id, int r_id)
{
    if (c_id < 0 || r_id < 0) {
        return StatusType::INVALID_INPUT;
    }

    auto record = m_records.getRecordInPlace(r_id);
    auto member = m_customers.find(c_id);
    if (record == nullptr || member == nullptr) {
        return StatusType::DOESNT_EXISTS;
    }

    if (member->isMember()) {
        member->buyCD(record->getPrice());
    }
    record->buyRecord();
    return StatusType::SUCCESS;
}


StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double amount)
{
    if (c_id1 < 0 || c_id2 < 0 || amount < 0 || c_id1 > c_id2) {
        return StatusType::INVALID_INPUT;
    }

    m_clubMembers.add_extra(amount, c_id2 - 1);
    m_clubMembers.add_extra(-amount, c_id1 - 1);
    return StatusType::SUCCESS;
}

Output_t<double> RecordsCompany::getExpenses(int c_id)
{
    if (c_id < 0) {
        return StatusType::INVALID_INPUT;
    }

    auto customer = m_customers.find(c_id);
    if (customer == nullptr || !customer->isMember()) {
        return StatusType::DOESNT_EXISTS;
    }

    double expenses = customer->getExpenses();
    if (customer->isMember()) {
        expenses -= m_clubMembers.sum_extras(c_id);
    }

    return expenses;
}

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2)
{
    if (r_id1 < 0 || r_id2 < 0) {
        return StatusType::INVALID_INPUT;
    }

    auto record1 = m_records.getRecordInPlace(r_id1);
    auto record2 = m_records.getRecordInPlace(r_id2);

    if (record1 == nullptr || record2 == nullptr) {
        return StatusType::DOESNT_EXISTS;
    }

    auto group1 = m_records.Find(r_id1);
    auto group2 = m_records.Find(r_id2);
    auto new_group = m_records.Union(group1, group2);

    if (new_group == nullptr) {
        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;
}


StatusType RecordsCompany::getPlace(int r_id, int* column, int* hight)
{
    if (r_id < 0 || column == nullptr || hight == nullptr) {
        return StatusType::INVALID_INPUT;
    }

    if (m_records.getRecordInPlace(r_id) == nullptr) {
        return StatusType::DOESNT_EXISTS;
    }

    *column = m_records.getColumn(r_id);
    *hight = m_records.getHight(r_id);

    return StatusType::SUCCESS;
}
