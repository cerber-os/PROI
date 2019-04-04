/*
 * File: tester.cpp
 * Author: Paweł Wieczorek
 * Date: 14 mar 2019
 * Description: Implementation of class used to test CircularList library
 */

#include <cassert>
#include <sstream>
#include <iostream>
#include "tester.h"
#include "circularList.h"
#include "circularList.cpp"
#include "realSet.h"

template <typename T>
Tester<T>::Tester( T* values ) {
    for(int i = 0; i < MAXIMUM_VALUES; i++)
        exampleValues[i] = values[i];
}

template<typename T>
void Tester<T>::run() {
    T1_GetElementFromEmptyList();
    T2_GetNextElementFromEmptyList();
    T3_CompareEmptyLists();
    T4_AppendElements();
    T5_RemoveElements();
    T6_GetElement();
    T7_GetNextElement();
    T8_CompareLists();
    T9_GetLengthOfList();
    T10_GetElementViaOperator();
    T11_CompareListsViaOperator();
    T12_PrintList();
    T13_PrintEmptyList();
    T14_StressTest();
}


template <typename T>
void Tester<T>::T1_GetElementFromEmptyList() {
    CircularList<T> list;
    try {
        list.getIth(0);
    } catch(const std::invalid_argument& exc) {
        return;
    }
    assert(false);
}

template <typename T>
void Tester<T>::T2_GetNextElementFromEmptyList() {
    CircularList<T> list;
    try {
        list.getNext(0);
    } catch(const std::invalid_argument& exc) {
        return;
    }
    assert(false);
}

template <typename T>
void Tester<T>::T3_CompareEmptyLists() {
    CircularList<T> list1;
    CircularList<T> list2;
    assert(list1.compare(list2));
}

template <typename T>
void Tester<T>::T4_AppendElements() {
    CircularList<T> list;
    for(int i = 0; i < 5; i++)
        list.append(exampleValues[i]);
    assert(list.getIth(0) == exampleValues[0]);
    assert(list.getIth(4) == exampleValues[4]);
}

template <typename T>
void Tester<T>::T5_RemoveElements() {
    CircularList<T> list;
    for(int i = 0; i < 5; i++)
        list.append(exampleValues[i]);

    list.remove(1);
    assert(list.getIth(1) == exampleValues[2]);
    assert(list.getLength() == 4);
}

template <typename T>
void Tester<T>::T6_GetElement() {
    CircularList<T> list;
    for(int i = 0; i < 5; i++)
        list.append(exampleValues[i]);

    for(int i = 0; i < 5; i++)
        assert(list.getIth(i) == exampleValues[i]);
}

template <typename T>
void Tester<T>::T7_GetNextElement() {
    CircularList<T> list;
    for(int i = 0; i < 5; i++)
        list.append(exampleValues[i]);

    for(int i = 0; i < 5; i++)
        assert(list.getNext(i) == exampleValues[(i+1)%5]);
}

template <typename T>
void Tester<T>::T8_CompareLists() {
    CircularList<T> list1;
    CircularList<T> list2;
    for(int i = 0; i < 5; i++)
        list1.append(exampleValues[i]);
    for(int i = 0; i < 5; i++)
        list2.append(exampleValues[i]);

    assert(list1.compare(list2));

    list2.append(exampleValues[3]);
    assert(!list1.compare(list2));
}

template <typename T>
void Tester<T>::T9_GetLengthOfList() {
    CircularList<T> list;
    for(int i = 0; i < 5; i++)
        list.append(exampleValues[i]);

    for(int i = 0; i < 2; i++)
        list.remove(i);
    assert(list.getLength() == 3);
}

template <typename T>
void Tester<T>::T10_GetElementViaOperator() {
    CircularList<T> list;
    for(int i = 0; i < 5; i++)
        list.append(exampleValues[i]);

    for(int i = 0; i < 5; i++)
        assert(list[i] == exampleValues[i]);
}

template <typename T>
void Tester<T>::T11_CompareListsViaOperator() {
    CircularList<T> list1;
    CircularList<T> list2;
    for(int i = 0; i < 5; i++)
        list1.append(exampleValues[i]);
    for(int i = 0; i < 5; i++)
        list2.append(exampleValues[i]);

    assert(list1 == list2);

    list2.append(exampleValues[3]);
    assert(list1 != list2);
}

template <typename T>
void Tester<T>::T12_PrintList() {
    CircularList<T> list;
    std::stringstream buffer, valid;

    list.append(exampleValues[0]);
    list.append(exampleValues[1]);
    buffer << list;

    valid << exampleValues[0] << ", " << exampleValues[1];
    assert(buffer.str() == valid.str());
}

template <typename T>
void Tester<T>::T13_PrintEmptyList() {
    CircularList<T> list;
    std::stringstream buffer;

    buffer << list;
    assert(buffer.str() == "<empty>");
}

template <typename T>
void Tester<T>::T14_StressTest() {
    CircularList<T> list1;

    for(int i = 0; i < 10000; i++)
        list1.append(exampleValues[i % 5]);
    assert(list1.getLength() == 10000);
    assert(list1[1000] == exampleValues[1000 % 5]);

    for(int i = 9999; i >= 0; i--)
        list1.remove(i);
    assert(list1.getLength() == 0);
    assert(list1.isEmpty());
}
