/*
 * File: swimmingPool.cpp
 * Author: Paweł Wieczorek
 * Date: 08 maj 2019
 * Description: Implementation of class representing swimming pool
 */

#include <thread>
#include <chrono>
#include "swimmingPool.h"
#include "randomGen.h"

SwimmingPool::SwimmingPool( std::string name, bool withDelays ) :
    name(std::move(name)), currentTimeTick(0), withDelays(withDelays) {}


// Simulate every place
long SwimmingPool::simulate() {
    for(Place* place : places) {
        if(withDelays)
            std::this_thread::sleep_for(std::chrono::milliseconds(genRandomNumber(400,450)));
        place->simulate(currentTimeTick);
    }

    return currentTimeTick++;
}

// Return reference to vector of places
std::vector<Place*>& SwimmingPool::getPlaces() {
    return places;
}

