/*
 * File: tester.h
 * Author: Paweł Wieczorek
 * Date: 14 mar 2019
 * Description: Header of file tester.cpp
 */

#ifndef PROJECT2_TESTER_H
#define PROJECT2_TESTER_H

/**
 * Class implementing CircularList library tests
 */
template <typename T>
class Tester {
private:
    static constexpr int MAXIMUM_VALUES = 5;
    T exampleValues[MAXIMUM_VALUES];
public:
    explicit Tester(T* values);
    void run();
    void T1_GetElementFromEmptyList();
    void T2_GetNextElementFromEmptyList();
    void T3_CompareEmptyLists();
    void T4_AppendElements();
    void T5_RemoveElements();
    void T6_GetElement();
    void T7_GetNextElement();
    void T8_CompareLists();
    void T9_GetLengthOfList();
    void T10_GetElementViaOperator();
    void T11_CompareListsViaOperator();
    void T12_PrintList();
    void T13_PrintEmptyList();
    void T14_StressTest();
};
#endif //PROJECT2_TESTER_H
