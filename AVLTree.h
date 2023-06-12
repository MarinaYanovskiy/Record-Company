#ifndef AVLTREE_H
#define AVLTREE_H

#include "AVLNode.h"
#include <iostream>

template <class K, class D>
class AVLTree {
public:
    AVLTree();
    ~AVLTree();
    void insert(K key, D data);
    void remove(K key);
    D find(K key) const;
    void print() const;
    D* test() const;
    D largest() const;

    class ReverseInorderIterator {
    public:
        ReverseInorderIterator(Node<K, D>* tree, int index)
            : m_size(0)
            , m_index(index)
        {
            if (tree == nullptr) {
                this->m_dataArray = new D[1];
                return;
            }

            m_size = tree->size();
            this->m_dataArray = new D[m_size + 1];
            tree->inOrderArray(this->m_dataArray, 1);
        }

        ~ReverseInorderIterator()
        {
            delete[] m_dataArray;
        }

        ReverseInorderIterator& operator++()
        {
            this->m_index--;
            return *this;
        }

        D* operator->()
        {
            return &this->m_dataArray[this->m_index];
        }

        D operator*() const
        {
            return this->m_dataArray[this->m_index];
        }

        bool operator==(const ReverseInorderIterator& other) const
        {
            return this->m_dataArray[m_index] == other.m_dataArray[other.m_index];
        }

        bool operator!=(const ReverseInorderIterator& other) const
        {
            return !(*this == other);
        }

    private:
        D* m_dataArray;
        int m_size;
        int m_index;
    };

    ReverseInorderIterator begin()
    {
        if (this->m_root == nullptr) {
            return ReverseInorderIterator(this->m_root, 0);
        }
        int size = this->m_root->size();
        return ReverseInorderIterator(this->m_root, size);
    }

    ReverseInorderIterator end()
    {
        return ReverseInorderIterator(this->m_root, 0);
    }

private:
    Node<K, D>* m_root;
};

template <class K, class D>
AVLTree<K, D>::AVLTree()
    : m_root(nullptr)
{
}

template <class K, class D>
AVLTree<K, D>::~AVLTree()
{
    if (m_root != nullptr) {
        delete m_root;
        this->m_root = nullptr;
    }
}

template <class K, class D>
void AVLTree<K, D>::insert(K key, D data)
{
    if (this->m_root == nullptr) {
        this->m_root = new Node<K, D>(key, data);
        return;
    }

    this->m_root->insert(key, data);
}

template <class K, class D>
void AVLTree<K, D>::remove(K key)
{
    if (this->m_root == nullptr) {
        return;
    }

    if (this->m_root->isLeaf() && this->m_root->find(key)) {
        delete this->m_root;
        this->m_root = nullptr;
        return;
    }

    this->m_root->remove(key);
}

template <class K, class D>
D AVLTree<K, D>::find(K key) const
{
    if (this->m_root == nullptr) {
        return nullptr;
    }

    return this->m_root->find(key);
}

template <class K, class D>
void AVLTree<K, D>::print() const
{
    if (this->m_root != nullptr) {
        this->m_root->print("", false);
    }
}

template <class K, class D>
D AVLTree<K, D>::largest() const 
{
    if (this->m_root == nullptr) {
        return nullptr;
    }

    return this->m_root->largest();
}
#endif
