/*
 * File: realSet.cpp
 * Author: Paweł Wieczorek
 * Date: 04 mar 2019 (chg: 19 mar 2019)
 * Description: Type used to store set of real numbers
 */

#include "realSet.h"
#include <iostream>
#include <cstring>


RealSet::RealSet() {
    set = new double[MAX_SIZE + 1];
    length = 0;
}

RealSet::RealSet(RealSet& oper) {
    set = new double[MAX_SIZE + 1];
    length = 0;
    operator=(oper);
}

RealSet::~RealSet()
{
    delete[] set;
}

/**
 * Checks if set contains given number
 * @param number
 * @return true | false
 */
bool RealSet::contains(double number) const {
    for(int i = 0; i < length; i++)
        if(set[i] == number)
            return true;
    return false;
}

/**
 * Adds number to set
 * @param number
 */
void RealSet::append(double number) {
    if(contains(number))
        return;

    if(length == MAX_SIZE)
        std::cerr << "Err: Max set size reached. Ignoring append request..." << std::endl;
    else
        set[length++] = number;
}

/**
 * Removes given number from set
 * @param number
 * @return removed number or -1 if it isn't in set
 */
double RealSet::remove(double number) {
    int indexOfNumber = -1;
    for (int i = 0; i < length; i++)
        if (set[i] == number) {
            indexOfNumber = i;
            break;
        }

    if (indexOfNumber == -1) {
        // There's no such number in set
        std::cerr << "Err: Attempted to remove not existing element. Returning -1..." << std::endl;
        return 0;
    } else if(indexOfNumber == length - 1)
        // It's the last value in set
        return set[length--];

    // It's typical case - insert last element in the place of removed one
    double retVal = set[indexOfNumber];
    set[indexOfNumber] = set[length - 1];
    length--;
    return retVal;
}

/**
 * Returns number of elements in set
 * @return length
 */
int RealSet::getLength() const {
    return length;
}

/**
 * Gets i-th element from set. Be careful, index of number could change after modification of set
 * @param index of element
 * @return value or -1 in case such index does not exist
 */
double RealSet::getIthElement(int index) const {
    if(index < 0 || index >= length) {
        std::cerr << "Err: Attempted to get not existing element. Returning -1..." << std::endl;
        return -1;
    }
    return set[index];
}

/**
 * Union of sets
 * @param oper
 * @return
 */
RealSet RealSet::operator+(const RealSet& oper) {
    RealSet newSet;

    for(int i = 0; i < getLength(); i++)
        newSet.append( getIthElement(i) );
    for(int i = 0; i < oper.getLength(); i++)
        if(!newSet.contains( oper.getIthElement(i) ))
            newSet.append(oper.getIthElement(i));
    return newSet;
}

void RealSet::operator+=(const RealSet& oper) {
    for(int i = 0; i < oper.getLength(); i++)
        if(!contains( oper.getIthElement(i) ))
            append(oper.getIthElement(i));
}

/**
 * Sets difference
 * @param oper
 * @return
 */
RealSet RealSet::operator-(const RealSet& oper) {
    RealSet newSet;

    for(int i = 0; i < getLength(); i++)
        if(!oper.contains( getIthElement(i) ))
            newSet.append(getIthElement(i));
    return newSet;
}

void RealSet::operator-=(const RealSet& oper) {

    for(int i = 0; i < oper.getLength(); i++)
        if(contains( oper.getIthElement(i) ))
            remove(oper.getIthElement(i));
}

/**
 * Sets intersection
 * @param oper
 * @return
 */
RealSet RealSet::operator*(const RealSet& oper) {
    RealSet newSet;
    for(int i = 0; i < getLength(); i++)
        if(oper.contains(getIthElement(i)))
            newSet.append(getIthElement(i));
    return newSet;
}

void RealSet::operator*=(const RealSet& oper) {
    for(int i = 0; i < getLength(); i++)
        if(!oper.contains(getIthElement(i)))
            remove(getIthElement(i--));     // We have removed element, but on its place the last one was placed
                                            // so by decreasing i we are checking also the new one
}

/**
 * Checks if two sets contains the same numbers
 * @param oper
 * @return true | false
 */
bool RealSet::operator==(const RealSet& oper) {
    if(getLength() != oper.getLength())
        return false;
    for(int i = 0; i < getLength(); i++)
        if(!oper.contains(getIthElement(i)))
            return false;
    return true;
}

bool RealSet::operator!=(const RealSet& oper) {
    if(getLength() != oper.getLength())
        return true;
    for(int i = 0; i < getLength(); i++)
        if(!oper.contains(getIthElement(i)))
            return true;
    return false;
}

/**
 * Returns max possible set sized. This can be changed by editing const value MAX_SIZE
 * @return max size of set
 */
int RealSet::getMaxSize() const {
    return MAX_SIZE;
}


RealSet& RealSet::operator=( const RealSet &oper ) {
    length = oper.getLength();
    memcpy(set, oper.set, MAX_SIZE * sizeof(double));
    return *this;
}

/**
 * Inserts text representation of set to stream
 * @param out
 * @param oper
 * @return
 */
std::ostream& operator<<(std::ostream& out, const RealSet& oper) {
    if(oper.getLength() == 0)
        out << "<empty>";
    else {
        for(int i = 0; i < oper.getLength() - 1; i++)
            out << oper.getIthElement(i) << ", ";

        out << oper.getIthElement(oper.getLength() - 1); // Don't print comma at the end of output
    }
    return out;
}
