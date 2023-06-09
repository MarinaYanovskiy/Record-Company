#ifndef HASH_HASHTABLE_H
#define HASH_HASHTABLE_H

#include <memory>
#include "AVLTree.h"
#include "Customer.h"
#include "HashFunc.h"

#define MIN_SIZE 2
#define INCREMENT_FACTOR 2
class hashTable {
private:
    int m_numOfObjects;
    int m_tableSize;
    HashFunc m_hashFunc;
    AVLTree<int, std::shared_ptr<Customer> >* m_hashTableWithTrees;

    void enlargeTable();

public:
    hashTable();
    ~hashTable();
    void insert(int key, std::shared_ptr<Customer> customer);
    std::shared_ptr<Customer> find(int key) const;

};


#endif //HASH_HASHTABLE_H
