// Author: xianmu <atangengineer@gmail.com>
// Created: 01/16/17
// Description:

#ifndef SKIP_LIST_H
#define SKIP_LIST_H
#pragma once

#include <vector>

#include "random.h"

template<class T>
struct ListNode {
    ListNode();
    ListNode(const T &v, ListNode *r = NULL, ListNode *d = NULL);
    ListNode(const ListNode &node);

    T value;
    ListNode *right;
    ListNode *down;
};

// TODO: allocator, comparator, thread-safety, iterator
template<class T>
class SkipList {
public:
    SkipList();
    ~SkipList();

    // 0: ok, -1: already exist
    int insert(const T &t);

    // 0: ok, -1: error
    int lookup(const T &t);

    // 0: ok, -1: do not contain this value
    int remove(const T &t);

private:
    int height;
    ListNode<T> head;

    static const int kBranching = 4;
};

template<class T>
ListNode<T>::ListNode() : right(NULL), down(NULL) { }

template<class T>
ListNode<T>::ListNode(const T &t, ListNode *r, ListNode *n)
    : value(t), right(r), down(n) { }

template<class T>
ListNode<T>::ListNode(const ListNode &node) : value(node.value), right(node.right), down(node.down) { }


template<class T>
SkipList<T>::SkipList() : height(0) { }

template<class T>
SkipList<T>::~SkipList() { }

template<class T>
int SkipList<T>::lookup(const T &t) {
    ListNode<T> *cursor = &head;
    while (cursor) {
        while (cursor->right && cursor->right->value < t) {
            cursor = cursor->right;
        }
        if (cursor->right && cursor->right->value == t) {
            // found
            return 0;
        }
        cursor = cursor->down;
    }
    return -1;
}

template<class T>
int SkipList<T>::insert(const T &t) {
    std::vector<ListNode<T>*> prev;
    ListNode<T> *cursor = &head;
    while (cursor) {
        while (cursor->right && cursor->right->value < t) {
            cursor = cursor->right;
        }
        if (cursor->right && cursor->right->value == t) {
            // already exist in skip-list
            return -1;
        }
        if (cursor == &head || cursor->value < t) {
            prev.push_back(cursor);
        }
        cursor = cursor->down;
    }

    // insert new node bottom-up
    int i = prev.size() - 1;
    ListNode<T> *tmp = NULL;
    for (; i >= 0; --i) {
        ListNode<T> *node = new ListNode<T>(t);
        node->right = prev[i]->right;
        node->down = tmp;
        tmp = node;
        prev[i]->right = node;
        if (TrueRandom::NextUInt32() % kBranching != 0) {
            break;
        }
    }

    if (i == -1) {
        head.down = new ListNode<T>(head);
    }

    return 0;
}

template<class T>
int SkipList<T>::remove(const T &t) {
    std::vector<ListNode<T>*> prev;
    ListNode<T> *cursor = &head;
    while (cursor) {
        while (cursor->right && cursor->right->value < t) {
            cursor = cursor->right;
        }
        if (cursor->right && cursor->right->value == t) {
            prev.push_back(cursor);
        }
        cursor = cursor->down;
    }
    if (prev.length() == 0) {
        return -1;
    }

    for (int i = 0; i < prev.length(); ++i) {
        ListNode<T> *tmp = prev[i]->right;
        prev[i]->right = tmp->right;
        delete tmp;
    }

    return 0;
}

#endif // SKIP_LIST_H
