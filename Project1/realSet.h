/*
 * File: realSet.h
 * Author: Paweł Wieczorek
 * Date: 04 mar 2019
 * Description: Header of file realSet.cpp
 */

#ifndef PROJECT1_REALSET_H
#define PROJECT1_REALSET_H

#include <cmath>
#include <ostream>

#define REAL_SET_MAX_SIZE   100

/**
 * Class implementing set of real numbers
 */
class RealSet {
    double* set;
    int length;
    const int MAX_SIZE = REAL_SET_MAX_SIZE;
public:
    RealSet();
    ~RealSet();

    bool    contains    (double number) const;
    void    append      (double number);
    double  remove      (double number);
    int     getLength()     const;
    int     getMaxSize()    const;
    double  getIthElement(int index) const;

    RealSet operator+   (const RealSet& oper);
    void    operator+=  (const RealSet& oper);
    RealSet operator-   (const RealSet& oper);
    void    operator-=  (const RealSet& oper);
    RealSet operator*   (const RealSet& oper);
    void    operator*=  (const RealSet& oper);
    bool    operator==  (const RealSet& oper);
    bool    operator!=  (const RealSet& oper);
};

std::ostream& operator<<(std::ostream& out, const RealSet& oper);

#endif //PROJECT1_REALSET_H
