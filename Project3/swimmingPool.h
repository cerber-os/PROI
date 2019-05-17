/*
 * File: swimmingPool.h
 * Author: Paweł Wieczorek
 * Date: 08 maj 2019
 * Description: Implementation of class representing swimming pool - header
 */

#ifndef PROJECT3_SWIMMINGPOOL_H
#define PROJECT3_SWIMMINGPOOL_H
#include <string>
#include <vector>
#include "place.h"

// Required to use vector of Place* here
class Place;

/**
 * SwimmingPool - class representing swimming pool
 *      fields:     name
 *                  currentTimeTick
 *                  withDelays - should simulation contain delays to slow down output
 *                  places - vector of pointers to available places in swimming pool
 */
class SwimmingPool {
    const std::string name;
    long currentTimeTick;
    bool withDelays;
    std::vector<Place*> places;

public:
    SwimmingPool(std::string name = "Generic AquaPark", bool withDelays = true);
    long                    simulate    ();
    std::vector<Place*>&    getPlaces   ();
};
#endif //PROJECT3_SWIMMINGPOOL_H
