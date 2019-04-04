/*
 * File: CircularList.h
 * Author: Paweł Wieczorek
 * Date: 14 mar 2019
 * Description: Header of file CicularList.cpp
 */

#ifndef PROJECT2_CIRCULARLIST_H
#define PROJECT2_CIRCULARLIST_H

#include <ostream>

/**
 * Class implementing node of list
 */
template <typename T>
class ListNode {
public:
    ListNode*       next;
    T               value;
    ListNode(ListNode* nextV, T valueV)
        {
            next = nextV;
            value = valueV;
        };
};

/**
 * Class implementing circular list
 */
template <typename T>
class CircularList {
private:
    ListNode<T>*    head;
    ListNode<T>*    tail;
    int             length;
public:
    CircularList();
    ~CircularList();
    void    append      (T value);
    void    remove      (int idx);
    bool    isEmpty     () const;
    int     getLength   () const;
    T&      getIth      (int idx) const;
    T&      getNext     (int idx) const;
    bool    compare     (const CircularList &list) const;

    T&      operator[]  (int idx) const;
    bool    operator==  ( const CircularList &list ) const;
    bool    operator!=  ( const CircularList &list ) const;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const CircularList<T>& list);

#endif //PROJECT2_CIRCULARLIST_H
