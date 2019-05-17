/*
 * File: swimmingPool.cpp
 * Author: anybody
 * Date: 08 maj 2019
 * Description:
 */

#include "swimmingPool.h"
#include "randomGen.h"
#include <thread>
#include <chrono>


SwimmingPool::SwimmingPool( std::string name ) : name(std::move(name)), currentTimeTick(0) {}


long SwimmingPool::simulate() {
    for(Place* place : places) {
        std::this_thread::sleep_for(std::chrono::milliseconds(genRandomNumber(400,450)));
        place->simulate(currentTimeTick);
    }

    for(Place* place : specialPlaces) {
        std::this_thread::sleep_for(std::chrono::milliseconds(genRandomNumber(400,450)));
        place->simulate(currentTimeTick);
    }

    return currentTimeTick++;
}

void SwimmingPool::addPlace(Place& place) {
    places.push_back(&place);
}

void SwimmingPool::addSpecialPlace(Place& place) {
    specialPlaces.push_back(&place);
}

std::vector<Place*>& SwimmingPool::getPlaces() {
    return places;
}

std::vector<Place*>& SwimmingPool::getSpecialPlaces() {
    return specialPlaces;
}
