/*
 * File: randomGen.cpp
 * Author: Paweł Wieczorek
 * Date: 09 maj 2019
 * Description: Small lib providing basic random number generator support in C++11
 */

#include "randomGen.h"

#include <chrono>
#include <random>
#include <stdexcept>

// Global object og mt19937
static std::mt19937 generator;

// Initialize generator with provided seed
void initializeRandomGen(unsigned int seed) {
    if(seed == 0)
        // If no seed provided, use system clock
        seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);
}

// Generate random number in given interval. Throws std::invalid_argument if size of interval is 0.
int genRandomNumber(int from, int to) {
    if(to == from)
        throw std::invalid_argument("{genRandomNumber}: Requested to get random number from interval of size zero ");
    return generator() % (to - from) + from;
}