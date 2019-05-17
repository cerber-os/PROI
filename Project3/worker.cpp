/*
 * File: worker.cpp
 * Author: Paweł Wieczorek
 * Date: 08 maj 2019
 * Description: Implementation of class representing workers of swimming pool
 */

#include "worker.h"

int Worker::highestUid = 0;
int Rescuer::highestUid = 0;
int Instructor::highestUid = 0;

std::string Worker::getName() {
    return name;
}

bool Worker::isFreeInstructor() {
    return false;
}

bool Worker::isFreeRescuer() {
    return false;
}

bool Worker::isInstructor() {
    return false;
}

bool Worker::isRescuer() {
    return false;
}

int Worker::getId() {
    return uid;
}

Instructor::Instructor(std::string displayedName) {
    name = std::move(displayedName);
    uid = highestUid++;
}

bool Instructor::isFreeInstructor() {
    return isFree;
}

bool Instructor::isInstructor() {
    return true;
}

void Instructor::setInstructorAvailability(bool free) {
    isFree = free;
}

Rescuer::Rescuer(std::string displayedName) {
    name = std::move(displayedName);
    uid = highestUid++;
}


bool Rescuer::isFreeRescuer() {
    return isFree;
}

bool Rescuer::isRescuer() {
    return true;
}
