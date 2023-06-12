#ifndef AVLNODE_H
#define AVLNODE_H

#include <iostream>

inline int max(int a, int b)
{
    return a > b ? a : b;
}

template <class K, class D>
class Node {
public:
    Node(K key, D data);
    Node(Node<K, D>& other) = default;
    ~Node();
    void insert(K key, D data);
    D find(K key) const;
    void remove(K key);
    void print(std::string prefix, bool isLeft);
    bool isLeaf() const;
    void inOrderArray(D* array, int index) const;
    int size() const;
    D largest() const;

private:
    K m_key;
    D m_data;
    int m_height;
    Node* m_left;
    Node* m_right;

    int rHeight() const;
    int lHeight() const;
    void rRotate();
    void lRotate();
    void updateHeight();
    void rebalance();
    void remove(K key, Node<K, D>* parent);
};

template <class K, class D>
Node<K, D>::Node(K key, D data)
    : m_key(key)
    , m_data(data)
    , m_height(1)
    , m_left(nullptr)
    , m_right(nullptr)
{
}

template <class K, class D>
Node<K, D>::~Node()
{
    // delete this->m_data;
    delete this->m_right;
    this->m_right = nullptr;
    delete this->m_left;
    this->m_left = nullptr;
}

template <class K, class D>
int Node<K, D>::lHeight() const
{
    return this->m_left != nullptr ? this->m_left->m_height : 0;
}

template <class K, class D>
int Node<K, D>::rHeight() const
{
    return this->m_right != nullptr ? this->m_right->m_height : 0;
}

template <class K, class D>
void Node<K, D>::updateHeight()
{
    this->m_height = max(this->rHeight(), this->lHeight()) + 1;
}

template <class K, class D>
void Node<K, D>::rebalance()
{
    int balanceFactor = this->lHeight() - this->rHeight();
    if (balanceFactor == 2) {
        // rotate left
        Node<K, D>* left = this->m_left; // cannot fail
        if (left->lHeight() < left->rHeight()) {
            left->lRotate();
        }
        this->rRotate();
        return;
    }

    if (balanceFactor == -2) {
        // rotate right
        Node<K, D>* right = this->m_right; // cannot fail
        if (right->lHeight() > right->rHeight()) {
            right->rRotate();
        }
        this->lRotate();
        return;
    }

    return;
}

template <class K, class D>
void Node<K, D>::rRotate()
{
    Node<K, D>* left = this->m_left;
    this->m_left = left->m_right;
    this->updateHeight();
    left->m_right = new Node<K, D>(*this);
    left->updateHeight();
    *this = *left;
    left->m_right = nullptr;
    left->m_left = nullptr;
    delete left;
}

template <class K, class D>
void Node<K, D>::lRotate()
{
    Node<K, D>* right = this->m_right;
    this->m_right = right->m_left;
    this->updateHeight();
    right->m_left = new Node<K, D>(*this);
    right->updateHeight();
    *this = *right;
    right->m_right = nullptr;
    right->m_left = nullptr;
    delete right;
}

template <class K, class D>
void Node<K, D>::insert(K key, D data)
{
    if (this->m_key == key) {
        return;
    }

    if (key > this->m_key) {
        if (this->m_right) {
            this->m_right->insert(key, data);
        } else {
            this->m_right = new Node<K, D>(key, data);
        }
    } else {
        if (this->m_left) {
            this->m_left->insert(key, data);
        } else {
            this->m_left = new Node<K, D>(key, data);
        }
    }

    this->updateHeight();
    this->rebalance();
}

template <class K, class D>
D Node<K, D>::find(K key) const
{
    if (this->m_key == key) {
        return this->m_data;
    }

    if (key > this->m_key) {
        if (this->m_right) {
            return this->m_right->find(key);
        }
        return nullptr;
    }

    if (key < this->m_key) {
        if (this->m_left) {
            return this->m_left->find(key);
        }
        return nullptr;
    }

    return nullptr;
}

template <class K, class D>
void Node<K, D>::remove(K key, Node<K, D>* parent)
{
    if (key > this->m_key) {
        if (this->m_right == nullptr) {
            return;
        }
        this->m_right->remove(key, this);
        this->updateHeight();
        this->rebalance();
        return;
    }

    if (key < this->m_key) {
        if (this->m_left == nullptr) {
            return;
        }
        this->m_left->remove(key, this);
        this->updateHeight();
        this->rebalance();
        return;
    }

    if (key != this->m_key) {
        return;
    }

    // current node is a leaf
    if (this->m_height == 1) {
        if (parent == nullptr) {
            delete this;
            return;
        }

        // update parent
        Node<K, D>** parents_son = parent->m_right == this ? &parent->m_right : &parent->m_left;
        *parents_son = nullptr;
        parent->updateHeight();
        parent->rebalance();
        delete this;
        return;
    }

    // node has only one son
    if ((this->m_right == nullptr) ^ (this->m_left == nullptr)) {
        Node<K, D>* son = this->m_right ? this->m_right : this->m_left;
        if (parent == nullptr) {
            // this == root
            *this = *son;
            son->m_right = nullptr;
            son->m_left = nullptr;
            delete son;
            return;
        }

        Node<K, D>** parents_son = parent->m_right == this ? &parent->m_right : &parent->m_left;
        // currently, parents_son points to this
        *parents_son = son;
        parent->updateHeight();
        parent->rebalance();
        this->m_right = nullptr;
        this->m_left = nullptr;
        delete this;
        return;
    }

    // otherwise (node has two sons)

    Node<K, D>* next_inorder = this->m_right;
    Node<K, D>* next_inorders_parent = this;
    while (next_inorder->m_left != nullptr) {
        next_inorders_parent = next_inorder;
        next_inorder = next_inorder->m_left;
    }

    // swap this and next_inorder
    K temp_key = this->m_key;
    D temp_data = this->m_data;
    this->m_key = next_inorder->m_key;
    this->m_data = next_inorder->m_data;
    next_inorder->m_key = temp_key;
    next_inorder->m_data = temp_data;

    // now that this and next_inorder are swapped
    // next_inorder holds the key that needs to be removed
    next_inorder->remove(key, next_inorders_parent);
}

template <class K, class D>
void Node<K, D>::remove(K key)
{
    this->remove(key, nullptr);
}

template <class K, class D>
void Node<K, D>::print(std::string prefix, bool isLeft)
{
    std::cout << prefix;
    std::cout << (isLeft ? "├──" : "└──");
    std::cout << this->m_key << std::endl;
    if (this->m_left) {
        this->m_left->print(prefix + (isLeft ? "│   " : "    "), true);
    }
    if (this->m_right) {
        this->m_right->print(prefix + (isLeft ? "│   " : "    "), false);
    }
}

template <class K, class D>
bool Node<K, D>::isLeaf() const
{
    return this->m_height == 1;
}

template <class K, class D>
int Node<K, D>::size() const
{
    int size = 1;
    if (this->m_right) {
        size += this->m_right->size();
    }

    if (this->m_left) {
        size += this->m_left->size();
    }
    return size;
}

template <class K, class D>
void Node<K, D>::inOrderArray(D* array, int index) const
{
    if (this->m_left) {
        this->m_left->inOrderArray(array, index);
        index += this->m_left->size();
    }

    array[index] = this->m_data;
    index++;

    if (this->m_right) {
        this->m_right->inOrderArray(array, index);
    }
}

template <class K, class D>
D Node<K, D>::largest() const
{
    auto node = this;
    while (node->m_right != nullptr) {
        node = node->m_right;
    }
    
    return node->m_data;
}
#endif
