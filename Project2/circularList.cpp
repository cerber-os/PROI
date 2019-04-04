/*
 * File: CircularList.cpp
 * Author: Paweł Wieczorek
 * Date: 14 mar 2019
 * Description: Implementation of circular list
 */

#include "circularList.h"
#include <ostream>

template <typename T>
CircularList<T>::CircularList() {
    head = nullptr;
    tail = nullptr;
    length = 0;
}

template <typename T>
CircularList<T>::~CircularList() {
    ListNode<T>* curEl = head;
    ListNode<T>* nextEl;
    if(head == nullptr)             // List is empty
        return;

    while( curEl != tail ) {
        nextEl = curEl->next;
        delete curEl;
        curEl = nextEl;
    }
    delete tail;                    // Remove last element
}

/**
 * Adds element to the end of the list
 * @tparam type supporting item assignment
 * @param value to be added
 */
template <typename T>
void CircularList<T>::append(T value) {
    ListNode<T>* newEl = new ListNode<T>(head, value);
    if(head == nullptr) {           // It's first element in the list
        newEl->next = newEl;
        head = newEl;
        tail = newEl;
    } else {
        tail->next = newEl;
        tail = newEl;
    }
    length++;
}

/**
 * Removes element placed at given index
 * @tparam type supporting item assignment
 * @param idx
 */
template <typename T>
void CircularList<T>::remove(int idx) {
    ListNode<T>* curEl = head;
    if(head == nullptr)             // Can't remove from empty list
        return;
    if(tail == head) {              // There's only one element
        delete head;
        head = nullptr;
        tail = nullptr;
        length--;
    } else {                        // General case
        for ( int i = 0; i < idx - 1; i++ )
            curEl = curEl->next;

        auto nextEl = curEl->next->next;
        if ( tail == curEl->next )
            tail = curEl;
        if ( head == curEl->next )
            head = nextEl;

        delete curEl->next;
        curEl->next = nextEl;
        length--;
    }
}

/**
 * Checks if list is empty
 * @return true | false
 */
template<typename T>
bool CircularList<T>::isEmpty() const {
    return length == 0;
}

/**
 * Returns length of list
 * @return int
 */
template<typename T>
int CircularList<T>::getLength() const {
    return length;
}

/**
 * Returns reference to the ith element in list
 * @param index of element
 * @return reference to the requested element
 */
template <typename T>
T& CircularList<T>::getIth(int idx) const {
    ListNode<T>* curEl = head;
    if(head == nullptr)             // Can't get element from empty list
        throw std::invalid_argument("Can't get element from empty list");

    for(int i = 0; i < idx; i++)
        curEl = curEl->next;
    return curEl->value;
}

/**
 * Returns reference to the (idx + 1) element in list
 * @param idx
 * @return reference to the requested element
 */
template <typename T>
T& CircularList<T>::getNext(int idx) const {
    ListNode<T>* curEl = head;
    if(head == nullptr)             // Can't get next element from empty list
        throw std::invalid_argument("Can't get element from empty list");

    for(int i = 0; i < idx; i++)
        curEl = curEl->next;
    curEl = curEl->next;
    return curEl->value;
}

/**
 * Checks if two lists contain the same elements in the same order
 * @param second list
 * @return true | false
 */
template<typename T>
bool CircularList<T>::compare(const CircularList<T> &list) const {
    if(length != list.getLength())
        return false;
    for(int i = 0; i < length; i++)
        if(getIth(i) != list[i])
            return false;
    return true;
}

/**
 * Returns reference to the ith element from list
 * @param idx
 * @return reference to the ith element
 */
template<typename T>
T &CircularList<T>::operator[](int idx) const {
    return getIth(idx);
}

template<typename T>
bool CircularList<T>::operator==(const CircularList &list) const {
    return compare(list);
}

template<typename T>
bool CircularList<T>::operator!=(const CircularList &list) const {
    return !compare(list);
}

/**
 * Inserts text representation of list to stream
 * @param out
 * @param list
 * @return
 */
template<typename T>
std::ostream& operator<<(std::ostream& out, const CircularList<T>& list) {
    if(list.getLength() == 0)
        out << "<empty>";
    else {
        for(int i = 0; i < list.getLength() - 1; i++)
            out << list.getIth(i) << ", ";

        out << list.getIth(list.getLength() - 1); // Don't print comma at the end of output
    }
    return out;
}
