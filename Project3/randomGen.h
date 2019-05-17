/*
 * File: randomGen.h
 * Author: Paweł Wieczorek
 * Date: 09 maj 2019
 * Description: Small lib providing basic random number generator support in C++11 - header file
 */

#ifndef PROJECT3_RANDOMGEN_H
#define PROJECT3_RANDOMGEN_H
/*
 * generator            - global object of Mersenne Twister 19937 generator used by functions in this file
 * initializeRandomGen  - initializes generator with provided seed; called with default argument
 *                              will set seed accordingly to system clock
 * genRandomNumber      - generates random number in provided interval. Throws std::invalid_argument if
 *                              size of interval is 0.
 */
void initializeRandomGen(unsigned int seed = 0);
int genRandomNumber(int from = 0, int to = 10);

#endif //PROJECT3_RANDOMGEN_H
