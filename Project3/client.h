/*
 * File: client.h
 * Author: Paweł Wieczorek
 * Date: 08 maj 2019
 * Description: Implementation of class representing clients of swimming pool - header file
 */

#ifndef PROJECT3_CLIENT_H
#define PROJECT3_CLIENT_H

#include <iostream>

/**
 * Client - class representing clients of swimming pool
 *      fields:     uid - unique id of object
 *                  experience
 *                  ticketValidUntil - time tick until his ticket is valid
 *                  attachedInstructorId - (-1) if instructor isn't attached, otherwise his id
 *                  highestUid - first available id (starts with 0)
 *      examples:   Client(currentTimeTick + 10, experience);
 */
class Client {
    int uid;
    int experience;
    int ticketValidUntil;
    int attachedInstructorId = -1;
    static int highestUid;

public:
    explicit Client(int ticketTime=0, int exp=1) : ticketValidUntil(ticketTime), uid(highestUid++), experience(exp) {};
    void        setTicketTime       (int);
    int         getTicketTime       ();
    void        setExperience       (int);
    int         getExperience       ();
    void        attachInstructor    (int);
    int         detachInstructor    ();
    bool        isInstructorAttached();
    void        levelUp             ();
    bool        isOutOfTime         (int);
    int         getId               ();
    std::string getName             ();
};
#endif //PROJECT3_CLIENT_H
