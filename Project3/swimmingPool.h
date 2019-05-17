/*
 * File: swimmingPool.h
 * Author: Paweł Wieczorek
 * Date: 08 maj 2019
 * Description:
 */

#ifndef PROJECT3_SWIMMINGPOOL_H
#define PROJECT3_SWIMMINGPOOL_H
#include <string>
#include <vector>
#include "place.h"

class Place;
class SwimmingPool {
    const std::string name;
    long currentTimeTick;
    std::vector<Place*> places;
    std::vector<Place*> specialPlaces;

public:
    explicit SwimmingPool(std::string name = "Generic AquaPark");
    long simulate();
    void addPlace(Place&);
    void addSpecialPlace(Place&);
    std::vector<Place*>& getPlaces();
    std::vector<Place*>& getSpecialPlaces();
};
#endif //PROJECT3_SWIMMINGPOOL_H
