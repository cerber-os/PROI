/*
 * File: client.cpp
 * Author: Paweł Wieczorek
 * Date: 08 maj 2019
 * Description: Implementation of class representing clients of swimming pool
 */

#include "client.h"

int Client::highestUid = 0;

void Client::setTicketTime(int time) {
    ticketValidUntil = time;
}

int Client::getTicketTime() {
    return ticketValidUntil;
}

void Client::setExperience(int exp) {
    experience = exp;
}

int Client::getExperience(){
    return experience;
}

void Client::attachInstructor(int id) {
    attachedInstructorId = id;
}

// Returns id of currently attached instructor or -1 if no one is attached
int Client::detachInstructor() {
    int id = attachedInstructorId;
    attachedInstructorId = -1;
    return id;
}

bool Client::isInstructorAttached() {
    return attachedInstructorId != -1;
}

// Increase experience by one
void Client::levelUp() {
    experience++;
}

// Checks if ticket is still valid in given time stamp
bool Client::isOutOfTime(int currentTimeStamp) {
    return ticketValidUntil < currentTimeStamp;
}

int Client::getId() {
    return uid;
}

// Returns string representing class by name and id
std::string Client::getName() {
    return "Client #" + std::to_string(uid);
}
