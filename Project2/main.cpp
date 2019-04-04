/*
 * File: main.cpp
 * Author: Paweł Wieczorek
 * Date: 14 mar 2019
 */

#include <iostream>
#include "tester.h"
#include "tester.cpp"
#include "realSet.h"

int main() {
    // Run tests for integers
    int exampleIntValues[] = {1,2,3,4,5};
    Tester<int> testForInt(exampleIntValues);
    testForInt.run();

    // Run tests for RealSet class
    RealSet t1, t2, t3, t4, t5;
    t1.append(1);
    t1.append(2);   // t1 = {1,2}
    t2.append(4);
    t2.append(1);   // t2 = {1,4}
    t3.append(2);   // t3 = {2}
    t4.append(3);
    t4.append(5);   // t4 = {3,5}
    t5.append(1);
    t5.append(2);   // t5 = {1,2}

    RealSet exampleRealSets[] = {t1,t2,t3,t4,t5};
    Tester<RealSet> testForRealSet(exampleRealSets);
    testForRealSet.run();

    std::cout << "No errors found!" << std::endl;
    return 0;
}
